// Livro

#ifndef LIVRO_H
#define LIVRO_H

#include "../system/system.h"

// Entrada: Ponteiro para um livro (livro *l).
// Retorno: Inteiro (1 para verdadeiro, 0 para falso).
// Pré-condição: Nenhuma.
// Pós-condição: Retorna 1 se o ponteiro para o livro é nulo, e 0 caso contrário.
int vazia(livro *l);

// Auxiliar

// Entrada: Ponteiro para o arquivo (FILE *arq) e ponteiro para o livro a ser inserido (livro *novo_livro).
// Retorno: Nenhum.
// Pré-condição: 'arq' deve estar aberto e 'novo_livro' deve ser um ponteiro válido.
// Pós-condição: O livro é inserido na árvore de dados e o cabeçalho do arquivo é atualizado.
void insere_livro(FILE *arq, livro *novo_livro);

// Entrada: Ponteiro para o arquivo (FILE *arq).
// Retorno: Nenhum.
// Pré-condição: O arquivo 'arq' deve estar aberto.
// Pós-condição: Solicita os dados de um novo livro ao usuário via console e o cadastra no sistema.
void cadastrar_livro(FILE *arq);

// Entrada: Ponteiro para o arquivo de livros (FILE *arq).
// Retorno: Nenhum.
// Pré-condição: Arquivo binário deve estar aberto.
// Pós-condição: Solicita um código ao usuário e, se o livro for encontrado, exibe todas as suas informações na tela.
void imprimir_dados_livro(FILE *arq);

// Entrada: Ponteiro para o arquivo de livros (FILE *arq).
// Retorno: Nenhum.
// Pré-condição: O arquivo 'arq' deve estar aberto.
// Pós-condição: Exibe na tela uma lista de todos os livros cadastrados, em ordem crescente de código.
void listar_livros(FILE *arq);

// Entrada: Ponteiro para o arquivo de livros (FILE *arq).
// Retorno: Nenhum.
// Pré-condição: O ponteiro de arquivo deve ser válido e aberto em modo de leitura binária.
// Pós-condição: O número total de livros cadastrados (excluindo os da lista de livres) é exibido na tela.
void calcular_total(FILE *arq);

// Entrada: Ponteiro para o arquivo de livros (FILE *arq).
// Retorno: Nenhum.
// Pré-condição: Arquivo binário deve estar aberto.
// Pós-condição: Solicita um código ao usuário e remove o livro correspondente, adicionando seu espaço à lista de livres.
void remover_livro(FILE *arq);

#endif