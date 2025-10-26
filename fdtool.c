#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Headers/leArquivo.h"
#include "Headers/operacoes.h"

char devolveOperacao(char *entrada) {
    char op, *aux;
    int i = 1;
    aux = strchr(entrada, 'l');

    op = aux[i++];
    while(op == ' ') 
        op = aux[i++];

    return op;
}

char *devolveNomeArquivo(char *entrada) {
    char *nomeArquivo;
    nomeArquivo = strchr(entrada, '-') + 5;

    while(nomeArquivo[0] == ' ')
        nomeArquivo++;
    
    nomeArquivo[strcspn(nomeArquivo, " ")] = '\0';
    return nomeArquivo;
}

char *devolveAtributoEntrada(char *entrada) {
    char *atributo;
    atributo = strrchr(entrada, '-') + 3;

    while(atributo[0] == ' ')
        atributo++;

    atributo[strcspn(atributo, " ")] = '\0';
    return atributo;
}

int main() {
    char entrada[100];
    char *nomeArquivo, op;

    printf("$ ");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0';
    while(strcmp(entrada, "sair")) {
        //switch case para os comandos
        op = devolveOperacao(entrada);
        switch (op) {
        case 'c':
            char copiaNomeArquivo[100];
            strcpy(copiaNomeArquivo, entrada);
            nomeArquivo = devolveNomeArquivo(entrada);
            
            FILE* arq = devolveArquivo(nomeArquivo);
            char* atr = devolveAtributos(arq);
            
            char* dep = devolveStringDependencias(arq);

            struct listaDependencias* listaDep = devolveDependencia(dep);;
            calculaFecho(listaDep, devolveAtributoEntrada(copiaNomeArquivo));
            

            free(atr);
            free(dep);
            free(listaDep->DF);
            free(listaDep);
            fclose(arq);
            break;

        case 'm':
            /* colocar a cobertura minima aqui */
            break;

        case 'k':
            printf("Chaves candidatas, ainda não implementado\n");
            break;

        case 'n':
            printf("Formas normais, ainda não implementado\n");
            break;
        default:
            printf("Operação inválida\n");
            break;
        }




        

        printf("$ ");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';
    }
    
    
}