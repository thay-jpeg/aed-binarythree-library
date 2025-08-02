// Livro

#ifndef LIVRO_H
#define LIVRO_H

#include "../system/system.h"

int vazia(livro * l);

//Auxiliar
void insere_livro(FILE *arq, livro *novo_livro);

void cadastrar_livro(FILE *arq);

//void imprimir_dados_livro(FILE *arq);

//void listar_livros(FILE *arq);

//void calcular_total(FILE *arq);

//void remover_livro(FILE *arq);

#endif