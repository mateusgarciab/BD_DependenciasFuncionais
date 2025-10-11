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


/* Só para testar */
int main() {
    
    FILE *arq = devolveArquivo("./exemplos/1.fds"); // Será que precisamos verificar se tem .fds ?
    
    
    fclose(arq);
    printf("Arquivo aberto\n");
    return 0;
}