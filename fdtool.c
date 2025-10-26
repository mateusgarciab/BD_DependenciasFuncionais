#include <stdio.h>
#include <string.h>

#include "Headers/leArquivo.h"

int main() {
    char entrada[100];
    char *nomeArquivo;

    printf("$ ");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0';
    while(strcmp(entrada, "sair")) {
        //switch case para os comandos
        nomeArquivo = strchr(entrada, '-') + 6;
        nomeArquivo[strcspn(nomeArquivo, " ")] = '\0';
        puts(nomeArquivo);

        FILE* arq = devolveArquivo(nomeArquivo);
        char* atr = devolveAtributos(arq);
        puts(atr);

        printf("$ ");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';
    }
    
    
}