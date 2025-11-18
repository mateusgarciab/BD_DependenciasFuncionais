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

char *calculaFecho(struct listaDependencias *lista, char *X){
    char *fecho = malloc(sizeof(char) * 26);
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
    //printf("%s\n", fecho);
    return fecho;
}

void calcularCoberturaMinima(struct Dependencia *DF, int qtd){
    //Etapa 1: Tornar o lado direito de cada dependência funcional unitário
    struct Dependencia *DF_unitario = NULL;
    int qtd_unitario = 0;

    for(int i = 0; i < qtd; i++){
        for(int j = 0; DF[i].direita[j] != '\0'; j++){
            DF_unitario = realloc(DF_unitario, sizeof(struct Dependencia) * (qtd_unitario + 1));
            strcpy(DF_unitario[qtd_unitario].esquerda, DF[i].esquerda);
            DF_unitario[qtd_unitario].direita[0] = DF[i].direita[j];
            DF_unitario[qtd_unitario].direita[1] = '\0';
            qtd_unitario++;
        }
    }
    /* printf("Cobertura mínima - Etapa 1 (lado direito unitário):\n");
    for(int i = 0; i < qtd_unitario; i++){
        printf("%s -> %s\n", DF_unitario[i].esquerda, DF_unitario[i].direita);
    } */

    //Etapa 2: Remover atributos estranhos do lado esquerdo
    struct listaDependencias *lista_temp;
    lista_temp = malloc(sizeof(struct listaDependencias));
    for(int i = 0; i < qtd_unitario; i++){
        for(int j = 0; DF_unitario[i].esquerda[j] != '\0'; j++){
            char temp[26];
            int k = 0;
            //cria uma cópia do lado esquerdo sem o atributo j
            for(int l = 0; DF_unitario[i].esquerda[l] != '\0'; l++){
                if(l != j){
                    temp[k++] = DF_unitario[i].esquerda[l];
                }
            }
            temp[k] = '\0';

            lista_temp->DF = DF_unitario;
            lista_temp->qtd = qtd_unitario;
            char *fecho = calculaFecho(lista_temp, temp);
            
            //verifica se o atributo da direita ainda pode ser derivado
            int podeDerivar = 0;
            for(int l = 0; fecho[l] != '\0'; l++){
                if(fecho[l] == DF_unitario[i].direita[0]){
                    podeDerivar = 1;
                    break;
                }
            }
            free(fecho);

            //se pode derivar, atualiza o lado esquerdo
            if(podeDerivar){
                strcpy(DF_unitario[i].esquerda, temp);
                j--; //ajusta o índice após a remoção
            }
        }
    }
    /* printf("Cobertura mínima - Etapa 2 (remover atributos estranhos do lado esquerdo):\n");
    for(int i = 0; i < qtd_unitario; i++){
        printf("%s -> %s\n", DF_unitario[i].esquerda, DF_unitario[i].direita);
    } */

    //Etapa 3: Remover dependências funcionais redundantes
    struct Dependencia *DF_minimo = malloc(sizeof(struct Dependencia) * qtd_unitario);
    int qtd_minimo = 0;
    for(int i = 0; i < qtd_unitario; i++){
        //cria uma cópia das dependências sem a i-ésima
        struct Dependencia *DF_temp = malloc(sizeof(struct Dependencia) * (qtd_unitario - 1));
        int k = 0;
        for(int j = 0; j < qtd_unitario; j++){
            if(j != i){
                DF_temp[k++] = DF_unitario[j];
            }
        }

        lista_temp->DF = DF_temp;
        lista_temp->qtd = qtd_unitario - 1;
        char *fecho = calculaFecho(lista_temp, DF_unitario[i].esquerda);

        //verifica se o atributo da direita ainda pode ser derivado
        int podeDerivar = 0;
        for(int l = 0; fecho[l] != '\0'; l++){
            if(fecho[l] == DF_unitario[i].direita[0]){
                podeDerivar = 1;
                break;
            }
        }
        free(fecho);
        free(DF_temp);

        //se não pode derivar, mantém a dependência funcional
        if(!podeDerivar){
            DF_minimo[qtd_minimo++] = DF_unitario[i];
        }
    }
    //printf("Cobertura mínima - Etapa 3 (remover dependências redundantes):\n");
    for(int i = 0; i < qtd_minimo; i++){
        printf("%s -> %s\n", DF_minimo[i].esquerda, DF_minimo[i].direita);
    }
}

void calcularChavesMinimas(struct listaDependencias *lista, char *U){
    
    

}