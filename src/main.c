// Programa principal

#include <stdio.h>
#include "system/system.h"

int main()
{
    FILE *arq;
    system("cls");

    arq = abrir_arquivo("livraria.bin");

    if (!arq)
    {
        printf("ERRO CRITICO: Nao foi possivel iniciar o sistema. Encerrando...\n");
        system("pause");
        return 1;
    }

    printf("Sistema de Livraria iniciando...\n");

    iniciar_sistema(arq);

    fclose(arq);
    printf("Sistema encerrado. Dados salvos.\n\n");

    system("pause");
    return 0;
}