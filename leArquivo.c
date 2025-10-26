#include <stdio.h>
#include <stdlib.h>

#include "Headers/leArquivo.h"

FILE *devolveArquivo(char *nome) {
    FILE *arq = fopen(nome, "r") ;
    if (!arq) {
        fprintf(stderr, "Erro ao abrir arquivo\n");
        exit (1);
    }

    return arq;
}

char *devolveAtributos(FILE *arq) {
    char *atributos = malloc(sizeof(char) * 26);
    int i = 0;
    char c; 

    c = fgetc(arq); // ignorando o primeiro U
    while ((c = fgetc(arq)) != '\n') {
        if ((c != ',') && (c != ' ') && (c != '{') && (c != '=') && (c != '}') && (c != ';'))
            atributos[i++] = c;
    }

    return atributos;
}

char *devolveDependencias(FILE *arq) {
    char *dependencias = malloc (sizeof (char) * 100);
    int i = 0;
    char c;

    c = fgetc(arq); // ignorando o primeiro F
    while ((c = fgetc(arq)) != EOF) {
        if ((c != ' ') && (c != '{') && (c != '=') && (c != '}') && (c != '\n')) {
            if (c == ';')
                dependencias[i++] = ',';
            else
                dependencias[i++] = c;
        }
    }
    return dependencias;
}

/* Só para testar */
/* int main() {
    printf("main do leaaaarquivo");
    FILE *arq = devolveArquivo("./exemplos/1.fds"); 
    char *atributos, *dependencias;

    printf("Arquivo aberto\n");
    atributos = devolveAtributos(arq);
    printf("Atributos lidos: %s\n", atributos);
    dependencias = devolveDependencias(arq);
    printf("Dependencias lidas: %s\n", dependencias);

    fclose(arq);
    free(atributos);
    free(dependencias);
    return 0;
} */