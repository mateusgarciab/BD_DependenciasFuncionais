#ifndef LISTA_BUSCALARGURA_H
#define LISTA_BUSCALARGURA_H

#include "operacoes.h"

struct lista {
    int inicio;
    int qnt;
    char **atributos;
};


struct lista* criaLista(char *atr);

int comparaAtributos(const void *a, const void *b);

void insereLista(struct lista *l, char *atr);

unsigned char listaVazia(struct lista *l);

char *devolveItemLista(struct lista *l);

void liberaLista(struct lista *l);

int ehChave(struct listaDependencias *lista, char *item, char *atr);

int fazParteChave(char letra, char *item);


#endif
