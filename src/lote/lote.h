// Carregar Arquivo

#ifndef LOTE_H
#define LOTE_H

#include "../system/system.h"

// Entrada: Ponteiro para o arquivo de dados principal (FILE *arq), que deve estar aberto em modo de leitura/escrita binária.
// Retorno: Nenhum (void).
// Pré-condição: O arquivo 'arq' deve ser um ponteiro válido para um arquivo aberto.
// Pós-condição: Os livros válidos contidos no arquivo de lote são inseridos na árvore de dados do arquivo principal 'arq'.
void carregar_lote(FILE *arq);

#endif