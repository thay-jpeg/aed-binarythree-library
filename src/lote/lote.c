// Implementação

#include "lote.h"

#define MAX_FILE 268
#define MAX_NAME 256
#define MAX_BUFFER 1024

// Entrada: Ponteiro para uma string (token).
// Retorno: Ponteiro para o inicio da string sem espaços nas bordas.
// Pré-condição: A entrada deve ser uma string C valida (terminada em nulo).
// Pós-condição: A string original eh modificada no local, removendo espaços do inicio e do fim.
static char *remove_espacos(char *token)
{

    char *final;

    // se for um espaço, avança ->
    while (isspace((unsigned char)*token))
        token++;

    // se for um token só de espaços, só retorna
    if (*token == 0)
        return token;

    // vai para o final da string token
    final = token + strlen(token) - 1;

    // se o ponteiro ainda nao ter chegado no comeco da string e for um espaço, avança <-
    while (final > token && isspace((unsigned char)*final))
        final--;

    // novo '\0'
    *(final + 1) = '\0';

    return token;
}

// Entrada: Ponteiro para o arquivo de dados principal (FILE *arq), que deve estar aberto em modo de leitura/escrita binária.
// Retorno: Nenhum (void).
// Pré-condição: O arquivo 'arq' deve ser um ponteiro válido para um arquivo aberto.
// Pós-condição: Os livros válidos contidos no arquivo de lote são inseridos na árvore de dados do arquivo principal 'arq'.
void carregar_lote(FILE *arq)
{
    char nome_arquivo[MAX_NAME]; // 255 carac. + '\0'
    char diretorio[MAX_FILE];    // 'example/' + 255 carac. + '.txt' + \0
    char buffer[MAX_BUFFER];
    FILE *arq_lote;

    printf("\n========================== Sistema de Carregamento em Lote ===========================\n\n");
    printf("Bem-vindo(a), Usuario! Antes de prosseguirmos, para realizar o carregamento de seu arquivo com sucesso:\n");
    printf("- O nome de seu arquivo texto deve ter, no maximo, 255 caracteres -\n\n");

    printf("Digite o nome do seu arquivo de lote (ex: dados): ");
    scanf("%255[^\n]%*c", nome_arquivo);

    snprintf(diretorio, sizeof(diretorio), "example/%s.txt", nome_arquivo);

    arq_lote = fopen(diretorio, "r");

    if (!arq_lote)
    {
        printf("ERRO CRITICO: Nao foi possivel abrir o arquivo de lote '%s.txt'.\n", nome_arquivo);
        return;
    }

    int count = 0;

    while (fgets(buffer, sizeof(buffer), arq_lote))
    {
        // caso tiver, remover quebra de linha do buffer
        buffer[strcspn(buffer, "\r\n")] = 0;
        char *ptr_choose = buffer;

        // se for um espaço, avança
        while (*ptr_choose && isspace((unsigned char)*ptr_choose))
            ptr_choose++;
        // se a linha for vazia, avança
        if (*ptr_choose == '\0')
            continue;

        char *token;
        char *pieces[8];

        // leitura entre ;
        token = strtok(buffer, ";");

        // caso de linhas vazias
        if (!token)
            continue;

        livro novo;
        // para guardar os ponteiros de cada parte do token

        for (int i = 0; i < 8; i++)
        {
            // se um dos tokens for nulo, preenche o array com string vazia
            pieces[i] = token ? remove_espacos(token) : "";
            token = strtok(NULL, ";");
        }

        novo.codigo = atoi(pieces[0]);
        strcpy(novo.titulo, pieces[1]);
        strcpy(novo.autor, pieces[2]);
        strcpy(novo.editora, pieces[3]);
        novo.edicao = atoi(pieces[4]);
        novo.ano = atoi(pieces[5]);
        novo.exemplares = atoi(pieces[6]);
        novo.preco = atof(pieces[7]);

        insere_livro(arq, &novo);
        count++;
    }

    printf("\nCarregamento em lote concluido! %d registros processados.\n", count);
    printf("\n======================================================================================\n");
}