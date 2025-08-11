// Implementação
#include <stdio.h>
#include "system.h"

// Entrada: nenhuma
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: O menu principal com as opcoes do sistema eh exibido na tela.
void exibir_menu()
{

    printf("\n======================================================================================\n");
    printf("                          SISTEMA DE GERENCIAMENTO DA LIVRARIA              ");
    printf("\n======================================================================================\n\n");
    printf("1- Cadastrar livro.\n");
    printf("2- Informacoes de um respectivo livro.\n");
    printf("3- Listar todos os livros cadastrados.\n");
    printf("4- Calcular total de livros cadastrados.\n");
    printf("5- Remover cadastro de um livro.\n");
    printf("6- Carregar arquivo em lote.\n");
    printf("7- Listar todos os registros livres.\n");
    printf("8- Imprimir chaves da arvore por niveis.\n");
    printf("0- Sair\n");
    printf("\n======================================================================================\n");

    printf("Digite a opcao que deseja:\n");
}

// Entrada: Ponteiro para o arquivo de dados (FILE *arq).
// Retorno: Nenhum.
// Pré-condição: O arquivo 'arq' deve ser válido e ter sido aberto com sucesso.
// Pós-condição: O sistema entra em um loop, exibindo o menu e processando a escolha do usuário até que a opção 0 (sair) seja digitada.
void iniciar_sistema(FILE *arq)
{
    int escolha;

    do
    {
        exibir_menu();
        scanf("%d%*c", &escolha);

        processar_sistema(arq, escolha);
        printf("\n");
        system("pause");
        system("cls");

    } while (escolha != 0);
}

// Entrada: Ponteiro para o arquivo (FILE *arq) e a opção do menu (int opcao).
// Retorno: Nenhum.
// Pré-condição: O arquivo 'arq' deve ser válido e aberto.
// Pós-condição: A função correspondente à opção escolhida pelo usuário é executada.
void processar_sistema(FILE *arq, int opcao)
{
    switch (opcao)
    {
    case 1:
        cadastrar_livro(arq);
        break;
    case 2:
        imprimir_dados_livro(arq);
        break;
    case 3:
        listar_livros(arq);
        break;
    case 4:
        calcular_total(arq);
        break;
    case 5:
        remover_livro(arq);
        break;
    case 6:
        carregar_lote(arq);
        break;
    case 7:
        imprimir_registros_livres(arq);
        break;
    case 8:
        imprimir_arvore_niveis(arq);
        break;
    case 0:
        break;
    default:
        printf("\nOpcao invalida. Tente novamente.\n");
        break;
    }
}

// Entrada: Ponteiro para o arquivo (FILE *arq) e ponteiro para o cabeçalho a ser escrito (cabecalho *cab).
// Retorno: Nenhum.
// Pré-condição: 'arq' deve estar aberto para escrita binária. 'cab' deve ser um ponteiro válido.
// Pós-condição: O conteúdo da struct 'cab' é escrito no início do arquivo 'arq'.
void escreve_cabecalho(FILE *arq, cabecalho *cab)
{
    fseek(arq, 0, SEEK_SET);
    fwrite(cab, sizeof(cabecalho), 1, arq);
}

// Entrada: Ponteiro para o arquivo (FILE *arq).
// Retorno: Ponteiro para uma struct 'cabecalho' alocada dinamicamente com os dados lidos.
// Pré-condição: 'arq' deve estar aberto para leitura e conter um cabeçalho válido.
// Pós-condição: O cabeçalho do arquivo é lido e retornado. O chamador é responsável por liberar a memória alocada.
cabecalho *le_cabecalho(FILE *arq)
{
    cabecalho *cab = (cabecalho *)malloc(sizeof(cabecalho));
    fseek(arq, 0, SEEK_SET);
    fread(cab, sizeof(cabecalho), 1, arq);
    return cab;
}

// Entrada: Ponteiro para o arquivo (FILE *arq), ponteiro para a struct livro a ser escrita (livro *novo), e a posição no arquivo (int pos).
// Retorno: Nenhum.
// Pré-condição: 'arq' deve estar aberto para escrita binária. 'novo' e 'pos' devem ser válidos.
// Pós-condição: O livro é escrito na posição especificada do arquivo.
void escreve_livro(FILE *arq, livro *novo, int pos)
{
    fseek(arq, sizeof(cabecalho) + pos * sizeof(livro), SEEK_SET);
    fwrite(novo, sizeof(livro), 1, arq);
}

// Entrada: Ponteiro para o arquivo (FILE *arq) e a posição do livro a ser lido (int pos).
// Retorno: Ponteiro para uma struct 'livro' alocada dinamicamente com os dados lidos.
// Pré-condição: 'arq' deve estar aberto para leitura. 'pos' deve ser uma posição válida.
// Pós-condição: O livro da posição especificada é lido e retornado. O chamador é responsável por liberar a memória alocada.
livro *le_livro(FILE *arq, int pos)
{
    livro *novo = malloc(sizeof(livro));
    fseek(arq, sizeof(cabecalho) + pos * sizeof(livro), SEEK_SET);
    fread(novo, sizeof(livro), 1, arq);
    return novo;
}

// Entrada: String com o nome base do arquivo (const char *nome_arquivo).
// Retorno: Ponteiro para o arquivo (FILE *) aberto, ou NULL em caso de erro crítico.
// Pré-condição: Nenhuma.
// Pós-condição: Abre o arquivo de dados. Se não existir, um novo arquivo vazio é criado e inicializado.
FILE *abrir_arquivo(const char *nome_arquivo)
{
    char caminho[256];

    snprintf(caminho, sizeof(caminho), "example/%s", nome_arquivo);

    FILE *arq = fopen(caminho, "rb+");

    if (!arq)
    {
        printf("Arquivo de dados nao encontrado. Criando um novo em '/example'...\n\n");

        arq = fopen(caminho, "wb+");

        if (!arq)
        {
            printf("ERRO CRITICO: Nao foi possivel criar o arquivo de dados.\n\n");
            return NULL;
        }

        cria_arquivo_vazio(arq);
    }
    else
        printf("Arquivo de dados '%s' carregado com sucesso.\n\n", nome_arquivo);

    return arq;
}

// Entrada: Ponteiro para o arquivo (FILE *arq).
// Retorno: Nenhum.
// Pré-condição: 'arq' deve estar aberto para escrita binária, geralmente no modo "wb+".
// Pós-condição: Um cabeçalho com valores iniciais padrão é escrito no arquivo.
void cria_arquivo_vazio(FILE *arq)
{
    cabecalho *cab = (cabecalho *)malloc(sizeof(cabecalho));
    cab->pos_raiz = -1;
    cab->pos_topo = 0;
    cab->pos_livre = -1;

    escreve_cabecalho(arq, cab);
    free(cab);
}

// Propósito: Imprime as posições dos registros livres do arquivo binário.
// Pré-condições: Arquivo binário 'arq' deve estar aberto.
// Pós-condições: As posições da lista de registros livres são exibidas na tela.
void imprimir_registros_livres(FILE *arq)
{
    printf("\n============================= Lista de Registros Livres ==============================\n\n");

    cabecalho *cab = le_cabecalho(arq);
    int pos_atual_livre = cab->pos_livre;

    if (pos_atual_livre == -1)
    {
        printf("Nao ha registros livres no sistema.\n");
    }
    else
    {
        printf("Posicoes dos registros na lista de livres (do inicio para o fim):\n");

        while (pos_atual_livre != -1)
        {
            printf(" -> Posicao no arquivo: %d\n", pos_atual_livre);

            livro *temp_livro = le_livro(arq, pos_atual_livre);

            pos_atual_livre = temp_livro->pos_dir;

            free(temp_livro);
        }
    }

    printf("\n======================================================================================\n");
    free(cab);
}

// Entrada: Ponteiro para a estrutura de controle da fila
// Retorno: Inteiro (booleano). Retorna 1 (verdadeiro) se a fila estiver vazia, ou 0 (falso) caso contrário.
// Pré-condição: Nenhuma
// Pós-condição: O estado da fila permanece inalterado, pois a função apenas realiza uma verificação.
int vazia_fila(fila *f)
{
    return (f == NULL || f->inicio == NULL);
}

// Entrada: Ponteiro para a fila ser completamente liberada da memória.
// Retorno: Nenhum
// Pré-condição: 'f' deve ser um ponteiro para uma fila válida.
// Pós-condição: Toda a memória dinâmica alocada para a fila e seus nós é liberada.
void liberar_fila(fila *f)
{
    if (!f)
        return;

    while (!vazia_fila(f))
        unqueue(f);

    free(f);
}

// Entrada: Nenhuma.
// Retorno: Um ponteiro para a nova estrutura de fila criada e inicializada. Retorna NULL em caso de falha na alocação de memória.
// Pré-condição: Nenhuma.
// Pós-condição: Uma nova fila vazia é criada na memória heap.
fila *criar_fila()
{
    fila *f = (fila *)malloc(sizeof(fila));
    if (f)
    {
        f->inicio = f->fim = NULL;
    }
    return f;
}

// Entrada: Ponteiro para a fila onde o elemento será inserido e o valor inteiro a ser adicionado.
// Retorno: Nenhum
// Pré-condição: 'f' deve apontar para uma fila válida e inicializada.
// Pós-condição: Um novo nó contendo o valor 'pos' é criado e adicionado ao final da fila.
void queue(fila *f, int pos)
{
    filaEndereco *novo = (filaEndereco *)malloc(sizeof(filaEndereco));
    if (!f)
    {
        printf("ERRO: Nao foi possivel alocar memoria para o objeto na fila.\n");
        return;
    }

    novo->pos = pos;
    novo->prox = NULL;

    // a fila estava fazia, primeiro livro a ser enfileirado
    if (!f->fim)
    {
        f->inicio = f->fim = novo;
    }
    // a fila possui livros ja enfileirados
    else
    {
        // atualiza os ponteiros do novo livro enfileirado no final da fila
        f->fim->prox = novo;
        f->fim = novo;
    }
}

// Entrada: Ponteiro para a fila da qual o elemento será removido.
// Retorno: O valor inteiro do elemento que estava no início da fila. Retorna -1 se a fila estiver vazia.
// Pré-condição: 'f' deve apontar para uma fila válida.
// Pós-condição: O primeiro nó da fila é removido e sua memória é liberada. O ponteiro 'inicio' da fila é atualizado para o próximo nó. Se a fila ficar vazia, 'inicio' e 'fim' se tornam NULL.
int unqueue(fila *f)
{
    // a fila esta vazia
    if (!f->inicio)
        return -1;

    filaEndereco *aux = f->inicio;
    int pos = aux->pos;

    // atualiza o comeco da fila
    f->inicio = f->inicio->prox;

    // se for o ultimo da fila
    if (!f->inicio)
        f->fim = NULL;

    free(aux);
    return pos;
}

// Entrada: Ponteiro para o arquivo de dados principal.
// Retorno: Nenhum
// Pré-condição: 'arq' deve ser um ponteiro válido para o arquivo binário.
// Pós-condição: Os códigos dos livros na árvore são exibidos no console, ordenados por nível, com cada nível sendo impresso em uma nova linha.
void imprimir_arvore_niveis(FILE *arq)
{

    printf("\n======================================================================================\n");
    printf("                                 Impressao por Niveis              ");
    printf("\n======================================================================================\n\n");

    cabecalho *cab = le_cabecalho(arq);

    if (cab->pos_raiz == -1)
    {
        printf("A arvore esta vazia.\n");
        printf("\n======================================================================================\n");
        free(cab);
        return;
    }

    fila *fila = criar_fila();
    queue(fila, cab->pos_raiz);

    int nivel = 1;

    while (!vazia_fila(fila))
    {
        int aux = 0;
        filaEndereco *temp = fila->inicio;

        while (temp)
        {
            aux++;
            temp = temp->prox;
        }

        printf("                                       Nivel %d                                 \n\n", nivel++);

        for (int i = 0; i < aux; i++)
        {
            int pos = unqueue(fila);

            livro *livro_atual = le_livro(arq, pos);

            if (livro_atual)
            {
                if (i == 0)
                    printf("                                       ");

                printf("  %d  ", livro_atual->codigo);

                if (livro_atual->pos_esq != -1)
                {
                    queue(fila, livro_atual->pos_esq);
                }
                if (livro_atual->pos_dir != -1)
                {
                    queue(fila, livro_atual->pos_dir);
                }

                free(livro_atual);
            }
        }
        printf("\n\n");
    }

    printf("\n======================================================================================\n\n");
    liberar_fila(fila);
    free(cab);
}