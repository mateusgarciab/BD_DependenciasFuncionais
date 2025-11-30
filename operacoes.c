#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "Headers/operacoes.h"
#include "Headers/listaDeBusca.h"

struct listaDependencias* devolveDependencia(char* dependencias) {
    struct listaDependencias *lista = malloc(sizeof(struct listaDependencias));
    lista->DF = NULL;
    lista->qtd = 0;

    for(int i = 0; i < (int)strlen(dependencias); i++){
        lista->DF = realloc(lista->DF, sizeof(struct Dependencia) * (lista->qtd + 1));

        int j = 0;
        while(dependencias[i] != '-'){
            lista->DF[lista->qtd].esquerda[j] = dependencias[i];
            j++;
            i++;
        }
        lista->DF[lista->qtd].esquerda[j] = '\0'; //finaliza a string da esquerda
        i += 2; //pula o '->'
        j = 0;

        while(dependencias[i] != ',' && i < (int)strlen(dependencias)){
            lista->DF[lista->qtd].direita[j] = dependencias[i];
            j++;
            i++;
        }
        lista->DF[lista->qtd].direita[j] = '\0'; //finaliza a string da direita
        lista->qtd++;
    }


    return lista;
}

char *calculaFecho(struct listaDependencias *lista, char *X){
    char *fecho = calloc(26, sizeof(char));
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

    qsort(fecho, tamanhoFecho, sizeof(char), comparaAtributos);

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

    //Etapa 2: Remover atributos estranhos do lado esquerdo
    for(int i = 0; i < qtd_unitario; i++){
        int tamanhoEsquerda = strlen(DF_unitario[i].esquerda);

        for(int j = 0; j < tamanhoEsquerda; j++){
            //cria uma cópia do lado esquerdo sem o j-ésimo atributo
            char ladoEsquerdoTemp[26];
            int k = 0;
            for(int l = 0; DF_unitario[i].esquerda[l] != '\0'; l++){
                if(l != j){
                    ladoEsquerdoTemp[k++] = DF_unitario[i].esquerda[l];
                }
            }
            ladoEsquerdoTemp[k] = '\0';

           int qtd_temp = qtd_unitario;
           struct Dependencia *DF_temp = malloc(sizeof(struct Dependencia) * qtd_temp);

           // copiar TODAS as dependências
           for (int m = 0; m < qtd_unitario; m++) {
               DF_temp[m] = DF_unitario[m];
           }


            //calcula o fecho do lado esquerdo temporário com DF_temp
            struct listaDependencias lista;
            lista.DF = DF_temp;
            lista.qtd = qtd_temp;

            char *fecho = calculaFecho(&lista, ladoEsquerdoTemp);

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

            //se pode derivar, atualiza o lado esquerdo da dependência funcional
            if(podeDerivar){
                strcpy(DF_unitario[i].esquerda, ladoEsquerdoTemp);
                tamanhoEsquerda--;
                j--; //ajusta o índice para o próximo caractere
            }
        }
    }

    //remover duplicatas antes da etapa 3
    for(int i = 0; i < qtd_unitario; i++){
        for(int j = i + 1; j < qtd_unitario; j++){
            if(strcmp(DF_unitario[i].esquerda, DF_unitario[j].esquerda) == 0 &&
               strcmp(DF_unitario[i].direita, DF_unitario[j].direita) == 0){
                //remover DF_unitario[j]
                for(int k = j; k < qtd_unitario - 1; k++){
                    DF_unitario[k] = DF_unitario[k + 1];
                }
                qtd_unitario--;
                j--; //ajusta o índice para o próximo caractere
            }
        }
    }

    //Etapa 3: Remover dependências funcionais redundantes
    struct Dependencia *DF_final = malloc(sizeof(struct Dependencia) * qtd_unitario);
    int qtd_final = 0;

    for(int i = 0; i < qtd_unitario; i++){
        //criar DF_temp = DF_unit sem a DF[i]
        int qtd_temp = qtd_unitario - 1;
        struct Dependencia *DF_temp = malloc(sizeof(struct Dependencia) * qtd_temp);

        int index = 0;
        for(int j = 0; j < qtd_unitario; j++){
            if(j != i){
                DF_temp[index++] = DF_unitario[j];
            }
        }

        struct listaDependencias lista;
        lista.DF = DF_temp;
        lista.qtd = qtd_temp;

        char *fecho = calculaFecho(&lista, DF_unitario[i].esquerda);

        //verifica se o atributo da direita ainda pode ser derivado
        int podeDerivar = 0;
        for(int j = 0; fecho[j] != '\0'; j++){
            if(fecho[j] == DF_unitario[i].direita[0]){
                podeDerivar = 1;
                break;
            }
        }

        free(fecho);
        free(DF_temp);

        //se não pode derivar, mantém a dependência funcional
        if(!podeDerivar){
            DF_final[qtd_final++] = DF_unitario[i];
        }
    }

    for(int i = 0; i < qtd_final; i++){
        printf("%s -> %s\n", DF_final[i].esquerda, DF_final[i].direita);
    }

    free(DF_unitario);
    free(DF_final);
}

int temNasChaves(struct chaves *c, char *atr) {
    int indiceC;
    for (int i = 0; i < c->qtd; i++) {
        indiceC = 0;

       for (int j = 0; c->chave[i][j] != '\0'; j++) {
            for (int k = 0; atr[k] != '\0'; k++) {
                if (c->chave[i][j] == atr[k]) {
                    indiceC++;
                }
            }
       }

       if (indiceC == (int)strlen(c->chave[i]))
            return 1;
    }
    return 0;
}

struct chaves *buscaLargura(struct listaDependencias *lista, char* atr) {
    struct chaves *c = malloc(sizeof(struct chaves));
    c->chave = calloc(100, sizeof(char*));
    c->qtd = 0;
    int chaveAchada = 0;
    char *aux = calloc(100, sizeof(char));

    struct lista *l = criaLista(atr);
    while (!listaVazia(l)) {
        char *item = devolveItemLista(l);
        chaveAchada = 0;
        
        if (ehChave(lista, item, atr) && (!temNasChaves(c, item))) {
            c->chave[c->qtd] = malloc(sizeof(char) * (strlen(item) + 1));
            strcpy(c->chave[c->qtd], item);
            c->qtd++;
            chaveAchada = 1;
        }

        if (!chaveAchada) {
            for (int i = 0; i < (int)strlen(atr); i++) {
                if (!fazParteChave(atr[i], item)) {
                    strcpy(aux, item);
                    strncat(aux, &atr[i], strlen(aux) + 1);
                    aux[strlen(item) + 1] = '\0';
                    insereLista(l, aux);
                }
            }
        }
    }

    free(aux);
    liberaLista(l); 
    return c;
}

int jaEhprimo(char *primos, char atr, int tamPrimos) {
    for (int i = 0; i < tamPrimos; i++) {
        if (atr == primos[i])
            return 1;
    }
    return 0;
}

int estaNasChaves(struct chaves *c, char *ladoEsquerdo) {
    for (int i = 0; i < c->qtd; i++)
        if (strcmp(c->chave[i], ladoEsquerdo) == 0)
            return 1;
    return 0;
}

char *ehBCNF(struct listaDependencias *l, struct chaves *c){
    char *naoChaves = NULL;
    for (int i = 0; i < l->qtd; i++) {
        /* para bcnf vertificar se lado esquerdo eh uma chave */
        if (!estaNasChaves(c, l->DF[i].esquerda)) {
            naoChaves = realloc(naoChaves, sizeof(char) * (strlen(l->DF[i].esquerda) + 1));
            strcpy(naoChaves, l->DF[i].esquerda);

            return naoChaves;
        }
    }

    return NULL;
}

char *eh3FN(struct listaDependencias *l, struct chaves *c, char *primos){
    //verificar se o lado esquerdo não é superchave e o lado direito tem atributo não primo
    for (int i = 0; i < l->qtd; i++) {
        //verificar se lado esquerdo é superchave
        int ehSuperChave = 0;
        for (int j = 0; j < c->qtd; j++) {
            if (strcmp(c->chave[j], l->DF[i].esquerda) == 0) {
                ehSuperChave = 1;
                break;
            }
        }

        if (!ehSuperChave) {
            //verificar se o lado direito tem atributo não primo
            for (int j = 0; l->DF[i].direita[j] != '\0'; j++) {
                int ehPrimo = 0;
                for (int k = 0; primos[k] != '\0'; k++) {
                    if (l->DF[i].direita[j] == primos[k]) {
                        ehPrimo = 1;
                        break;
                    }
                }
                if (!ehPrimo) {
                    /* guardar o lado esquerdo e dereito no vetor e retornar */
                    char *naoPrimo = malloc(sizeof(char) * 3);
                    naoPrimo[0] = l->DF[i].direita[j];
                    naoPrimo[1] = (char)i;
                    naoPrimo[2] = '\0';
                    return naoPrimo;
                }
            }
        }
    }

    return NULL;
}

void formasNormais(struct listaDependencias *l, char *atr) {
    struct chaves *c = buscaLargura(l, atr);
    char *primos = malloc(sizeof(char) * 26);
    int tamPrimos = 0; 

    for (int i = 0; i < c->qtd; i++){
        for (int j = 0; c->chave[i][j] != '\0'; j++){
            if (!jaEhprimo(primos, c->chave[i][j], tamPrimos)) {
                primos[tamPrimos] = c->chave[i][j];
                tamPrimos++;
            }
        }
    }

    qsort(primos, tamPrimos, sizeof(char), comparaAtributos);
    primos[tamPrimos] = '\0';

    char *naoChaves = ehBCNF(l, c);
    if(naoChaves != NULL)
        printf("BCNF VIOLATIONS\n");
    else
        printf("A relação está em BCNF\n");
    
    char *naoPrimos = eh3FN(l, c, primos);
    if(naoPrimos != NULL)
        printf("3FN VIOLATIONS\n");
    else
        printf("A relação está em 3FN\n");


    //imprimir naoChaves
    if(naoChaves != NULL) {
        for(int i = 0; i < l->qtd; i++)
            if(strcmp(naoChaves, l->DF[i].esquerda) == 0){
                printf("VIOLATION BCNF: %s -> %s (%s not superkey)\n", l->DF[i].esquerda, l->DF[i].direita, naoChaves);
            }
    }
    //imprimir naoPrimos
    if(naoPrimos != NULL) {
        int index = (int)naoPrimos[1];
        printf("VIOLATION 3FN: %s -> %s (%c not prime, %s not superkey)\n", l->DF[index].esquerda, l->DF[index].direita, naoPrimos[0], l->DF[index].esquerda);
    }

    free(naoChaves);
    free(naoPrimos);
    free(primos);
    for (int i = 0; i < c->qtd; i++) {
        free(c->chave[i]);
    }
    free(c->chave);
    free(c);
}