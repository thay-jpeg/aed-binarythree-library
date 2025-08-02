// Implementação

#include "livro.h"

int vazia(livro *l)
{
    return (l == NULL);
}

static int insere_livro_recursivo(FILE *arq, int pos_atual, livro *novo_livro)
{
    // lugar vago na arvore
    if (pos_atual == -1)
    {
        cabecalho *cab = le_cabecalho(arq);
        int nova_pos = obter_posicao_livre(arq, cab);

        novo_livro->pos_esq = -1;
        novo_livro->pos_dir = -1;
        novo_livro->livre = 1; // posicao ocupada da arvore

        escreve_livro(arq, novo_livro, nova_pos);

        escreve_cabecalho(arq, cab);

        free(cab);

        return nova_pos;
    }

    livro *atual = le_livro(arq, pos_atual);

    //se for menor que o valor da raiz atual, esquerda
    if (novo_livro->codigo < atual->codigo)
    {
        int pos_filho_esq = insere_livro_recursivo(arq, atual->pos_esq, novo_livro);
        atual->pos_esq = pos_filho_esq;
    }
    //se for maior, direita
    else
    {
        int pos_filho_dir = insere_livro_recursivo(arq, atual->pos_dir, novo_livro);
        atual->pos_dir = pos_filho_dir;
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

    int nova_raiz = insere_livro_recursivo(arq, pos_raiz, novo_livro);

    // se a raiz tiver sido alterada
    if (cab->pos_raiz != nova_raiz)
    {
        cab->pos_raiz = nova_raiz;
        escreve_cabecalho(arq, cab);
    }

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