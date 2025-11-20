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
    char *atributos = calloc(26, sizeof(char));
    int i = 0;
    char c; 

    c = fgetc(arq); // ignorando o primeiro U
    while ((c = fgetc(arq)) != '\n') {
        if ((c != ',') && (c != ' ') && (c != '{') && (c != '=') && (c != '}') && (c != ';'))
            atributos[i++] = c;
    }

    return atributos;
}

char *devolveStringDependencias(FILE *arq) {
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
