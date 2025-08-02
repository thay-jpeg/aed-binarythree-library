// Sistema de Gerenciamento

#ifndef SYSTEM_H
#define SYSTEM_H

#include "storage.h"
#include "../lote/lote.h"
#include "../livro/livro.h"

void exibir_menu();

void iniciar_sistema(FILE *arq);

void processar_sistema(FILE *arq, int opcao);

void escreve_cabecalho(FILE *arq, cabecalho *cab);

cabecalho *le_cabecalho(FILE *arq);

void escreve_livro(FILE *arq, livro *novo, int pos);

livro *le_livro(FILE *arq, int pos);

FILE *abrir_arquivo(const char *nome_arquivo);

void cria_arquivo_vazio(FILE *arq);

int obter_posicao_livre(FILE *arq, cabecalho *cab);

//void imprimir_registros_livres(FILE *arq);

//void imprimir_arvore_niveis(FILE *arq);

#endif