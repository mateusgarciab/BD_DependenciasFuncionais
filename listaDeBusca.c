#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Headers/listaDeBusca.h"
#include "Headers/operacoes.h"


struct lista* criaLista(char *atr) {
    struct lista *l = malloc(sizeof(struct lista));
    l->inicio = 0;
    l->qnt = 0;
    l->atributos = malloc(sizeof(char*) * 100);

    int nAtr = strlen(atr);
    for (int i = 0; i < nAtr; i++) {
        l->atributos[i] = malloc(sizeof(char) * 2);
        l->atributos[i][0] = atr[i];
        l->atributos[i][1] = '\0';
        l->qnt++;
        l->total_alocado++;
    }

    return l;
}

int comparaAtributos(const void *a, const void *b) {
    return (*(char*)a - *(char*)b);
}

void insereLista(struct lista *l, char *atr) {
    qsort(atr, strlen(atr), sizeof(char), comparaAtributos);
    for (int i = l->inicio; i < l->qnt + l->inicio; i++) {
        if (strcmp(l->atributos[i], atr) == 0)
            return;
    }

    l->atributos[l->inicio + l->qnt] = malloc(sizeof(char) * (strlen(atr) + 1));
    strcpy(l->atributos[l->inicio + l->qnt], atr);
    
    if(l->inicio + l->qnt >= l->total_alocado){
        l->total_alocado = l->inicio + l->qnt + 1;
    }

    l->qnt++;
}

unsigned char listaVazia(struct lista *l) {
    unsigned char vazio;
    if (l->qnt == 0)
        vazio = 1;
    else
        vazio = 0;
    return vazio;
}

char *devolveItemLista(struct lista *l) {
    if (listaVazia(l))
        return NULL;

    l->qnt--;
    return l->atributos[l->inicio++];
}

void liberaLista(struct lista *l) {
    for (int i = 0; i < l->total_alocado; i++) {
        if(l->atributos[i] != NULL)
            free(l->atributos[i]);
    }
    free(l->atributos);
    free(l);
}

int ehChave(struct listaDependencias *lista, char *item, char *atr) {
    char *fecho = calculaFecho(lista, item);
    qsort(fecho, strlen(fecho), sizeof(char), comparaAtributos);

    int ehChave = strcmp(fecho, atr);
    free(fecho);
    if (ehChave == 0)
        return 1;
    else
        return 0;
}

int fazParteChave(char letra, char *item) {
    for (int i = 0; item[i] != '\0'; i++) {
        if (item[i] == letra)
            return 1;
    }
    return 0;
}
