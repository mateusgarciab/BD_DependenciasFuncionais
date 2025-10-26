#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "Headers/operacoes.h"

struct listaDependencias* devolveDependencia(char* dependencias) {
    struct Dependencia *DF = NULL;
    int qtd = 0; //quantidade de dependências
    
    for(int i = 0; i < (int)strlen(dependencias); i++){
        DF = realloc(DF, sizeof(struct Dependencia) * (qtd + 1));

        int j = 0;
        while(dependencias[i] != '-'){
            DF[qtd].esquerda[j] = dependencias[i];
            j++;
            i++;
        }
        DF[qtd].esquerda[j] = '\0'; //finaliza a string da esquerda
        i += 2; //pula o '->'
        j = 0;

        while(dependencias[i] != ',' && i < (int)strlen(dependencias)){
            DF[qtd].direita[j] = dependencias[i];
            j++;
            i++;
        }
        DF[qtd].direita[j] = '\0'; //finaliza a string da direita
        qtd++;
    }
    struct listaDependencias *lista = malloc(sizeof(struct listaDependencias));
    lista->DF = DF;
    lista->qtd = qtd;

    return lista;
}

void calculaFecho(struct listaDependencias *lista, char *X){
    char fecho[26];
    int tamanhoFecho = 0;

    int i = 0;
    while(X[i] != '\0'){
        fecho[tamanhoFecho] = X[i];
        tamanhoFecho++;
        i++;
    }

    int mudou;
    do{
        mudou = 0;
        for(int j = 0; j < lista->qtd; j++){
            int podeAdicionar = 1;
            //verifica se todos os atributos da esquerda estão no fecho
            for(int k = 0; lista->DF[j].esquerda[k] != '\0'; k++){
                int encontrado = 0;
                for(int l = 0; l < tamanhoFecho; l++){
                    if(lista->DF[j].esquerda[k] == fecho[l]){
                        encontrado = 1;
                        break;
                    }
                }
                if(!encontrado){
                    podeAdicionar = 0;
                    break;
                }
            }

            //se pode adicionar, adiciona os atributos da direita ao fecho
            if(podeAdicionar){
                for(int k = 0; lista->DF[j].direita[k] != '\0'; k++){
                    int jaExiste = 0;
                    for(int l = 0; l < tamanhoFecho; l++){
                        if(lista->DF[j].direita[k] == fecho[l]){
                            jaExiste = 1;
                            break;
                        }
                    }
                    if(!jaExiste){
                        fecho[tamanhoFecho] = lista->DF[j].direita[k];
                        tamanhoFecho++;
                        mudou = 1;
                    }
                }
            }
        }
    }while(mudou);
    fecho[tamanhoFecho] = '\0';

    //imprime fecho
    printf("%s\n", fecho);
}