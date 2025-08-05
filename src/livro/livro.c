// Implementação

#include "livro.h"
#include <stdio.h>
#include <stdlib.h>

int vazia(livro *l)
{
    return (l == NULL);
}

static int insere_livro_recursivo(FILE *arq, int pos_atual, livro *novo_livro, cabecalho *cab)
{
    // lugar vago na arvore
    if (pos_atual == -1)
    {
        int nova_pos;

        // se tiver posicao livre
        if (cab->pos_livre != -1)
        {
            nova_pos = cab->pos_livre;
            livro *aux = le_livro(arq, cab->pos_livre);
            cab->pos_livre = aux->pos_dir;
            free(aux);
        }

        // nao tem posicao livre, usar do topo
        else
            nova_pos = cab->pos_topo++;

        novo_livro->pos_esq = -1;
        novo_livro->pos_dir = -1;

        escreve_livro(arq, novo_livro, nova_pos);

        return nova_pos;
    }

    livro *atual = le_livro(arq, pos_atual);

    // se for menor que o valor da raiz atual, esquerda
    if (novo_livro->codigo < atual->codigo)
    {
        int pos_filho_esq = insere_livro_recursivo(arq, atual->pos_esq, novo_livro, cab);
        atual->pos_esq = pos_filho_esq;
    }
    // se for maior, direita
    else if (novo_livro->codigo > atual->codigo)
    {
        int pos_filho_dir = insere_livro_recursivo(arq, atual->pos_dir, novo_livro, cab);
        atual->pos_dir = pos_filho_dir;
    }
    else
    {
        printf("\nAVISO: Um livro com o codigo %02d ja existe. Nao eh possivel cadastrar livros duplicados.\n", novo_livro->codigo);
    }

    // salva as alterações no arquivo de esq e dir
    escreve_livro(arq, atual, pos_atual);
    free(atual);

    return pos_atual;
}

void insere_livro(FILE *arq, livro *novo_livro)
{
    cabecalho *cab = le_cabecalho(arq);
    int pos_raiz = cab->pos_raiz;

    cab->pos_raiz = insere_livro_recursivo(arq, pos_raiz, novo_livro, cab);

    escreve_cabecalho(arq, cab);

    free(cab);
}

void cadastrar_livro(FILE *arq)
{

    livro novo_livro;

    printf("\n=============================== Cadastro de novo livro ===============================\n");
    printf("\nDigite as credenciais a seguir:\n");
    printf("Codigo: ");
    scanf("%d%*c", &novo_livro.codigo);
    printf("Titulo (MAX. 150 carac.): ");
    scanf("%150[^\n]%*c", novo_livro.titulo);
    printf("Autor (MAX. 200 carac.): ");
    scanf("%200[^\n]%*c", novo_livro.autor);
    printf("Editora (MAX. 50 carac.): ");
    scanf("%50[^\n]%*c", novo_livro.editora);
    printf("Numero da edicao: ");
    scanf("%d%*c", &novo_livro.edicao);
    printf("Ano: ");
    scanf("%d%*c", &novo_livro.ano);
    printf("Quantidade de exemplares: ");
    scanf("%d%*c", &novo_livro.exemplares);
    printf("Preco de venda: ");
    scanf("%lf%*c", &novo_livro.preco);

    while (novo_livro.preco < 0)
    {
        printf("\nCusto de obra invalido. Por favor, insira um valor legitimo.\n\n");
        printf("Preco de venda: ");
        scanf("%lf%*c", &novo_livro.preco);
    }

    insere_livro(arq, &novo_livro);

    printf("\nLivro cadastrado com sucesso!\n");
    printf("\n======================================================================================\n");
}

static void listar_livros_recursivo(FILE *arq, int pos_atual)
{
    if (pos_atual == -1)
    {
        return;
    }

    livro *atual = le_livro(arq, pos_atual);

    listar_livros_recursivo(arq, atual->pos_esq);

    printf("Codigo: %d\n", atual->codigo);
    printf("Titulo: %s\n", atual->titulo);
    printf("Autor: %s\n", atual->autor);
    printf("Exemplares: %d\n\n", atual->exemplares);
    printf("--------------------------------------------------\n");

    listar_livros_recursivo(arq, atual->pos_dir);

    free(atual);
}

void listar_livros(FILE *arq)
{
    cabecalho *cab = le_cabecalho(arq);

    printf("\n============================= Lista de Livros Cadastrados ============================\n\n");

    if (cab->pos_raiz == -1)
    {
        printf("Nenhum livro cadastrado no sistema.\n");
    }
    else
    {
        printf("--------------------------------------------------\n");
        listar_livros_recursivo(arq, cab->pos_raiz);
    }

    printf("\n======================================================================================\n");

    free(cab);
}

// Propósito: Função auxiliar para buscar um livro pelo código na árvore de forma recursiva.
// Pré-condições: Arquivo binário aberto, posição do nó atual e código a ser buscado.
// Pós-condições: Retorna a posição do livro no arquivo se encontrado, ou -1 caso contrário.
static int busca_livro_recursivo(FILE *arq, int pos_atual, int codigo_busca)
{

    if (pos_atual == -1)
    {
        return -1;
    }

    livro *atual = le_livro(arq, pos_atual);
    int pos_encontrada = -1;

    if (codigo_busca == atual->codigo)
    {
        pos_encontrada = pos_atual;
    }

    else if (codigo_busca < atual->codigo)
    {
        pos_encontrada = busca_livro_recursivo(arq, atual->pos_esq, codigo_busca);
    }
    else //(codigo_busca > atual->codigo)
    {
        pos_encontrada = busca_livro_recursivo(arq, atual->pos_dir, codigo_busca);
    }

    free(atual);
    return pos_encontrada;
}

// Propósito: Dado um código, imprime as informações do respectivo livro.
// Pré-condições: Arquivo binário de livros aberto.
// Pós-condições: As informações do livro são exibidas na tela, ou uma mensagem de erro se o livro não for encontrado.
void imprimir_dados_livro(FILE *arq)
{
    int codigo_busca;
    printf("\nDigite o codigo do livro que deseja buscar: ");
    scanf("%d%*c", &codigo_busca);

    cabecalho *cab = le_cabecalho(arq);

    int pos_livro = busca_livro_recursivo(arq, cab->pos_raiz, codigo_busca);

    printf("\n=============================== Dados do Livro =====================================\n\n");

    if (pos_livro != -1)
    {

        livro *encontrado = le_livro(arq, pos_livro);
        printf("Codigo:       %d\n", encontrado->codigo);
        printf("Titulo:       %s\n", encontrado->titulo);
        printf("Autor:        %s\n", encontrado->autor);
        printf("Editora:      %s\n", encontrado->editora);
        printf("Edicao:       %d\n", encontrado->edicao);
        printf("Ano:          %d\n", encontrado->ano);
        printf("Exemplares:   %d\n", encontrado->exemplares);
        printf("Preco:        R$ %.2f\n", encontrado->preco);
        free(encontrado);
    }
    else
    {
        printf("Livro com o codigo %d nao foi encontrado no sistema.\n", codigo_busca);
    }

    printf("\n======================================================================================\n");

    free(cab);
}