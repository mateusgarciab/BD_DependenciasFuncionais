#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Headers/buscaLargura.h"
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
    }

    return l;
}

int comparaAtributos(const void *a, const void *b) {
    return (*(char*)a - *(char*)b);
}

void insereLista(struct lista *l, char *atr) {
    /* printf("Inserindo %s na lista\n", atr); */
    qsort(atr, strlen(atr), sizeof(char), comparaAtributos);
    for (int i = l->inicio; i < l->qnt + l->inicio; i++) {
        if (strcmp(l->atributos[i], atr) == 0)
            return;
    }

    l->atributos[l->inicio + l->qnt] = malloc(sizeof(char) * (strlen(atr) + 1));
    strcpy(l->atributos[l->inicio + l->qnt], atr);
    
    l->qnt++;
    /* printf("Inserido de vdd %s %d\n", l->atributos[l->inicio + l->qnt - 1], l->qnt); */
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
    for (int i = 0; i < l->qnt; i++) {
        free(l->atributos[i]);
    }
    free(l->atributos);
    free(l);
}

void imprimeLista(struct lista *l) { /* Para depuração, apagar depois */
    /* printf("Lista:\n"); */
    for (int i = l->inicio; i < l->qnt + l->inicio; i++) {
        /* printf("%s ", l->atributos[i]); */
    }
    /* printf("%d itens na lista.", l->qnt); */
    /* printf("\n"); */
}

int ehChave(struct listaDependencias *lista, char *item, char *atr) {
    char *fecho = calculaFecho(lista, item);
    qsort(fecho, strlen(fecho), sizeof(char), comparaAtributos);
    /* printf("Fecho de %s: %s\n", item, fecho); */

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

struct chaves *buscaLargura(struct listaDependencias *lista, char* atr) {
    struct chaves *c = malloc(sizeof(struct chaves));
    c->chave = malloc(sizeof(char*) * 100);
    c->qtd = 0;
    int chaveAchada = 0, tamChave = 0;
    char *aux = malloc(sizeof(char) * 100);

    struct lista *l = criaLista(atr);
    while (!listaVazia(l)) {
        char *item = devolveItemLista(l);
        /* printf("Item removido: %s, %d\n", item, l->qnt); */
        if (chaveAchada) {
            if ((int)strlen(item) > tamChave) {
                l->qnt = 0;
                continue;
            }
        }
        
        if (ehChave(lista, item, atr)) {
            /* printf("=========== Chave encontrada: %s\n", item); */
            c->chave[c->qtd] = item;
            c->qtd++;
            chaveAchada = 1;
            tamChave = strlen(item);
        }



        for (int i = 0; i < (int)strlen(atr); i++) {
            if ((!fazParteChave(atr[i], item)) && (!chaveAchada)) {
                strcpy(aux, item);
                strncat(aux, &atr[i], strlen(aux) + 1);
                aux[strlen(item) + 1] = '\0';
                /* puts(aux); */
                insereLista(l, aux);
            }
        }
        /* imprimeLista(l); */
    }

    free(aux);
    liberaLista(l); 

    printf("Chaves encontradas:\n");
    for (int i = 0; i < c->qtd; i++) {
        printf("%s\n", c->chave[i]);
    }

    return c;
}
