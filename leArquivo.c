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
    char *atributos = malloc(sizeof(char) * 27); // 0 para o numero de atributos e outras 26 para caber o alfabeto inteiro

    //Fazer laço pegando cada atributo e colocando no vetor
    //E colocar o tamanho no atributos[0]

    return atributos;
}

/* Só para testar */
int main() {
    
    FILE *arq = devolveArquivo("./exemplos/1.fds"); 
    char *atributos = devolveArquivo(arq);

    free(atributos);
    fclose(arq);
    printf("Arquivo aberto\n");
    return 0;
}