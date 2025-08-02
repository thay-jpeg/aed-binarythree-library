// Estrutura da Árvore Binária de Busca

#ifndef STORAGE_H
#define STORAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EDITORA 51
#define MAX_TITULO 151
#define MAX_AUTOR 201

typedef struct
{
    int pos_raiz;
    int pos_topo;
    int pos_livre;
} cabecalho;

typedef struct
{
    int codigo;
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    char editora[MAX_EDITORA];
    int edicao;
    int ano;
    int exemplares;
    double preco;

    int livre;
    int pos_esq;
    int pos_dir;

} livro;

#endif