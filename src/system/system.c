// Implementação

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
        // calcular_total(arq);
        break;
    case 5:
        // remover_livro(arq);
        break;
    case 6:
        // carregar_lote(arq);
        break;
    case 7:
        // imprimir_registros_livres(arq);
        break;
    case 8:
        // imprimir_arvore_niveis(arq);
        break;
    case 0:
        break;
    default:
        printf("\nOpcao invalida. Tente novamente.\n");
        break;
    }
}

void escreve_cabecalho(FILE *arq, cabecalho *cab)
{
    fseek(arq, 0, SEEK_SET);
    fwrite(cab, sizeof(cabecalho), 1, arq);
}

cabecalho *le_cabecalho(FILE *arq)
{
    cabecalho *cab = (cabecalho *)malloc(sizeof(cabecalho));
    fseek(arq, 0, SEEK_SET);
    fread(cab, sizeof(cabecalho), 1, arq);
    return cab;
}

void escreve_livro(FILE *arq, livro *novo, int pos)
{
    fseek(arq, sizeof(cabecalho) + pos * sizeof(livro), SEEK_SET);
    fwrite(novo, sizeof(livro), 1, arq);
}

livro *le_livro(FILE *arq, int pos)
{
    livro *novo = malloc(sizeof(livro));
    fseek(arq, sizeof(cabecalho) + pos * sizeof(livro), SEEK_SET);
    fread(novo, sizeof(livro), 1, arq);
    return novo;
}

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

void cria_arquivo_vazio(FILE *arq)
{
    cabecalho *cab = (cabecalho *)malloc(sizeof(cabecalho));
    cab->pos_raiz = -1;
    cab->pos_topo = 0;
    cab->pos_livre = -1;

    escreve_cabecalho(arq, cab);
    free(cab);
}
