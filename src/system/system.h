// Sistema de Gerenciamento

#ifndef SYSTEM_H
#define SYSTEM_H

#include "storage.h"
#include "../lote/lote.h"
#include "../livro/livro.h"

// Entrada: Nenhuma.
// Retorno: Nenhum.
// Pré-condição: Nenhuma.
// Pós-condição: O menu principal de opções do sistema é exibido na tela
void exibir_menu();

// Entrada: Ponteiro para o arquivo de dados (FILE *arq).
// Retorno: Nenhum.
// Pré-condição: O arquivo 'arq' deve ser válido e ter sido aberto com sucesso.
// Pós-condição: O sistema entra em um loop, exibindo o menu e processando a escolha do usuário até que a opção 0 (sair) seja digitada.
void iniciar_sistema(FILE *arq);

// Entrada: Ponteiro para o arquivo (FILE *arq) e a opção do menu (int opcao).
// Retorno: Nenhum.
// Pré-condição: O arquivo 'arq' deve ser válido e aberto.
// Pós-condição: A função correspondente à opção escolhida pelo usuário é executada.
void processar_sistema(FILE *arq, int opcao);

// Entrada: Ponteiro para o arquivo (FILE *arq) e ponteiro para o cabeçalho a ser escrito (cabecalho *cab).
// Retorno: Nenhum.
// Pré-condição: 'arq' deve estar aberto para escrita binária. 'cab' deve ser um ponteiro válido.
// Pós-condição: O conteúdo da struct 'cab' é escrito no início do arquivo 'arq'.
void escreve_cabecalho(FILE *arq, cabecalho *cab);

// Entrada: Ponteiro para o arquivo (FILE *arq).
// Retorno: Ponteiro para uma struct 'cabecalho' alocada dinamicamente com os dados lidos.
// Pré-condição: 'arq' deve estar aberto para leitura e conter um cabeçalho válido.
// Pós-condição: O cabeçalho do arquivo é lido e retornado. O chamador é responsável por liberar a memória alocada.
cabecalho *le_cabecalho(FILE *arq);

// Entrada: Ponteiro para o arquivo (FILE *arq), ponteiro para a struct livro a ser escrita (livro *novo), e a posição no arquivo (int pos).
// Retorno: Nenhum.
// Pré-condição: 'arq' deve estar aberto para escrita binária. 'novo' e 'pos' devem ser válidos.
// Pós-condição: O livro é escrito na posição especificada do arquivo.
void escreve_livro(FILE *arq, livro *novo, int pos);

// Entrada: Ponteiro para o arquivo (FILE *arq) e a posição do livro a ser lido (int pos).
// Retorno: Ponteiro para uma struct 'livro' alocada dinamicamente com os dados lidos.
// Pré-condição: 'arq' deve estar aberto para leitura. 'pos' deve ser uma posição válida.
// Pós-condição: O livro da posição especificada é lido e retornado. O chamador é responsável por liberar a memória alocada.
livro *le_livro(FILE *arq, int pos);

// Entrada: String com o nome base do arquivo (const char *nome_arquivo).
// Retorno: Ponteiro para o arquivo (FILE *) aberto, ou NULL em caso de erro crítico.
// Pré-condição: Nenhuma.
// Pós-condição: Abre o arquivo de dados. Se não existir, um novo arquivo vazio é criado e inicializado.
FILE *abrir_arquivo(const char *nome_arquivo);

// Entrada: Ponteiro para o arquivo (FILE *arq).
// Retorno: Nenhum.
// Pré-condição: 'arq' deve estar aberto para escrita binária, geralmente no modo "wb+".
// Pós-condição: Um cabeçalho com valores iniciais padrão é escrito no arquivo.
void cria_arquivo_vazio(FILE *arq);

// Entrada: Ponteiro para o arquivo (FILE *arq) e ponteiro para o cabeçalho (cabecalho *cab).
// Retorno: Inteiro representando a posição livre encontrada.
// Pré-condição: 'arq' e 'cab' devem ser ponteiros válidos.
// Pós-condição: Retorna uma posição disponível, seja da lista de livres ou do topo do arquivo.
int obter_posicao_livre(FILE *arq, cabecalho *cab);

// Entrada: Ponteiro para o arquivo (FILE *arq).
// Retorno: Nenhum.
// Pré-condição: Arquivo binário 'arq' deve estar aberto.
// Pós-condição: As posições da lista de registros livres são exibidas na tela.
void imprimir_registros_livres(FILE *arq);

// Entrada: Ponteiro para a estrutura de controle da fila
// Retorno: Inteiro (booleano). Retorna 1 (verdadeiro) se a fila estiver vazia, ou 0 (falso) caso contrário.
// Pré-condição: Nenhuma
// Pós-condição: O estado da fila permanece inalterado, pois a função apenas realiza uma verificação.
int vazia_fila(fila *f);

// Entrada: Ponteiro para a fila ser completamente liberada da memória.
// Retorno: Nenhum
// Pré-condição: 'f' deve ser um ponteiro para uma fila válida.
// Pós-condição: Toda a memória dinâmica alocada para a fila e seus nós é liberada.
void liberar_fila(fila *f);

// Entrada: Nenhuma.
// Retorno: Um ponteiro para a nova estrutura de fila criada e inicializada. Retorna NULL em caso de falha na alocação de memória.
// Pré-condição: Nenhuma.
// Pós-condição: Uma nova fila vazia é criada na memória heap.
fila *criar_fila();

// Entrada: Ponteiro para a fila onde o elemento será inserido e o valor inteiro a ser adicionado.
// Retorno: Nenhum
// Pré-condição: 'f' deve apontar para uma fila válida e inicializada.
// Pós-condição: Um novo nó contendo o valor 'pos' é criado e adicionado ao final da fila.
void queue(fila *f, int pos);

// Entrada: Ponteiro para a fila da qual o elemento será removido.
// Retorno: O valor inteiro do elemento que estava no início da fila. Retorna -1 se a fila estiver vazia.
// Pré-condição: 'f' deve apontar para uma fila válida.
// Pós-condição: O primeiro nó da fila é removido e sua memória é liberada. O ponteiro 'inicio' da fila é atualizado para o próximo nó. Se a fila ficar vazia, 'inicio' e 'fim' se tornam NULL.
int unqueue(fila *f);

// Entrada: Ponteiro para o arquivo de dados principal.
// Retorno: Nenhum
// Pré-condição: 'arq' deve ser um ponteiro válido para o arquivo binário.
// Pós-condição: Os códigos dos livros na árvore são exibidos no console, ordenados por nível, com cada nível sendo impresso em uma nova linha.
void imprimir_arvore_niveis(FILE *arq);

#endif