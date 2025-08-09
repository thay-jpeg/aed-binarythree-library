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
        printf("\nAVISO: Um livro com o codigo %03d ja existe. Nao eh possivel cadastrar livros duplicados.\n", novo_livro->codigo);
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

    printf("%03d | %-35s | %-20s | %d\n", atual->codigo, atual->titulo, atual->autor, atual->exemplares);

    listar_livros_recursivo(arq, atual->pos_dir);

    free(atual);
}

void listar_livros(FILE *arq)
{
    cabecalho *cab = le_cabecalho(arq);

    printf("\n============================= Lista de Livros Cadastrados ============================\n");

    if (cab->pos_raiz == -1)
    {
        printf("Nenhum livro cadastrado no sistema.\n");
    }
    else
    {
        printf("%-3s | %-35s | %-20s | %s\n", "Cod", "Titulo", "Autor", "Exemplares");
        printf("======================================================================================\n");

        listar_livros_recursivo(arq, cab->pos_raiz);
    }

    printf("======================================================================================\n");

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
        printf("Codigo:       %03d\n", encontrado->codigo);
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
        printf("Livro com o codigo %03d nao foi encontrado no sistema.\n", codigo_busca);
    }

    printf("\n====================================================================================\n");

    free(cab);
}

// Entrada: Ponteiro para o arquivo, a posição do registro e um ponteiro para uma struct 'livro' de destino.
// Retorno: 1 se a leitura for bem-sucedida, 0 caso contrario.
// Pré-condição: O ponteiro de arquivo deve ser válido. O ponteiro 'destino' deve apontar para uma área de memória alocada.
// Pós-condição: A struct 'destino' é preenchida com os dados lidos da posição especificada no arquivo.
static int busca_livro(FILE *arq, int pos, livro *destino)
{

    fseek(arq, sizeof(cabecalho) + pos * sizeof(livro), SEEK_SET);

    if (fread(destino, sizeof(livro), 1, arq) == 1)
        return 1;

    return 0;
}

// Entrada: Ponteiro para o arquivo de livros.
// Retorno: Nenhum
// Pré-condição: O ponteiro de arquivo deve ser valido e aberto em "r+b".
// Pós-condição: O numero total de livros cadastrados (excluindo os da lista de livres) eh exibido na tela.
void calcular_total(FILE *arq)
{

    cabecalho *cab = le_cabecalho(arq);

    int temp = 0;
    int total_topo = cab->pos_topo;
    int livre_atual = cab->pos_livre;
    livro aux;

    while (livre_atual != -1)
    {
        if (busca_livro(arq, livre_atual, &aux))
        {
            temp++;
            livre_atual = aux.pos_dir;
        }
        else
        {
            printf("ERRO: Nao foi possivel acessar o arquivo de dados...\n");
            livre_atual = -1;
        }
    }
    printf("\n======================================================================================\n");
    printf("                            Total de livros cadastrados: %d         ", total_topo - temp);
    printf("\n======================================================================================\n");

    free(cab);
}

// Propósito: Adiciona a posição de um registro removido à lista de livres.
// Pré-condições: Arquivo aberto, posição a ser liberada e ponteiro para o cabeçalho.
// Pós-condições: O registro na 'pos_removida' é encadeado no início da lista de livres.
static void adicionar_a_lista_livre(FILE *arq, int pos_removida, cabecalho *cab)
{
    livro *livro_removido = le_livro(arq, pos_removida);

    livro_removido->pos_dir = cab->pos_livre;

    cab->pos_livre = pos_removida;

    escreve_livro(arq, livro_removido, pos_removida);

    free(livro_removido);
}

// Propósito: Encontrar o nó com o maior código na subárvore fornecida (predecessor em-ordem).
// Pré-condições: Arquivo aberto, posição inicial da subárvore (raiz da subárvore esquerda).
// Pós-condições: Retorna a posição do nó com o maior valor na subárvore.
int encontrar_maior_predecessor(FILE *arq, int pos_inicio)
{
    livro *atual = le_livro(arq, pos_inicio);
    int pos_predecessor = pos_inicio;

    while (atual->pos_dir != -1)
    {
        pos_predecessor = atual->pos_dir;
        free(atual); // Libera o livro lido anteriormente
        atual = le_livro(arq, pos_predecessor);
    }

    free(atual);
    return pos_predecessor;
}

// Propósito: Função recursiva para buscar e remover um livro da árvore.
// Pré-condições: Arquivo aberto, posição do nó atual, código do livro a ser removido e cabeçalho.
// Pós-condições: Retorna a nova posição do nó atual após a eventual remoção.
int remover_livro_recursivo(FILE *arq, int pos_atual, int codigo_remover, cabecalho *cab)
{
    
    if (pos_atual == -1)
    {
        return -1;
    }

    livro *atual = le_livro(arq, pos_atual);

    if (codigo_remover < atual->codigo)
    {
        atual->pos_esq = remover_livro_recursivo(arq, atual->pos_esq, codigo_remover, cab);
    }
    else if (codigo_remover > atual->codigo)
    {
        atual->pos_dir = remover_livro_recursivo(arq, atual->pos_dir, codigo_remover, cab);
    }
    else
    {
        if (atual->pos_esq == -1 && atual->pos_dir == -1)
        {
            adicionar_a_lista_livre(arq, pos_atual, cab);
            free(atual);
            return -1; 
        }
        
        else if (atual->pos_esq == -1)
        {
            int pos_filho_dir = atual->pos_dir;
            adicionar_a_lista_livre(arq, pos_atual, cab);
            free(atual);
            return pos_filho_dir; 
        }
        else if (atual->pos_dir == -1)
        {
            int pos_filho_esq = atual->pos_esq;
            adicionar_a_lista_livre(arq, pos_atual, cab);
            free(atual);
            return pos_filho_esq; 
        }
        
        else
        {
        
            int pos_predecessor = encontrar_maior_predecessor(arq, atual->pos_esq);
            livro *predecessor = le_livro(arq, pos_predecessor);

            atual->codigo = predecessor->codigo;
            strcpy(atual->titulo, predecessor->titulo);
            strcpy(atual->autor, predecessor->autor);
            strcpy(atual->editora, predecessor->editora);
            atual->edicao = predecessor->edicao;
            atual->ano = predecessor->ano;
            atual->exemplares = predecessor->exemplares;
            atual->preco = predecessor->preco;

            free(predecessor);

            atual->pos_esq = remover_livro_recursivo(arq, atual->pos_esq, atual->codigo, cab);
        }
    }

    escreve_livro(arq, atual, pos_atual);
    free(atual);
    return pos_atual;
}

// Propósito: Remove um livro do cadastro dado o seu código.
// Pré-condições: Arquivo binário de livros aberto.
// Pós-condições: O livro é removido da árvore e seu registro adicionado à lista de livres.
void remover_livro(FILE *arq)
{
    int codigo_remover;
    printf("\n=============================== Remocao de Livro =====================================\n");
    printf("\nDigite o codigo do livro que deseja remover: ");
    scanf("%d%*c", &codigo_remover);

    cabecalho *cab = le_cabecalho(arq);
    int pos_raiz_inicial = cab->pos_raiz;

    cab->pos_raiz = remover_livro_recursivo(arq, cab->pos_raiz, codigo_remover, cab);

    if (pos_raiz_inicial != -1 && cab->pos_raiz == pos_raiz_inicial && busca_livro_recursivo(arq, cab->pos_raiz, codigo_remover) != -1)
    {
         printf("\nAVISO: Livro com codigo %03d nao foi encontrado para remocao.\n", codigo_remover);
    }
    else if (pos_raiz_inicial == -1)
    {
        printf("\nAVISO: A arvore esta vazia. Nenhum livro para remover.\n");
    }
    else
    {
        printf("\nLivro com codigo %03d removido com sucesso.\n", codigo_remover);
    }

    escreve_cabecalho(arq, cab);

    printf("\n======================================================================================\n");
    free(cab);
}