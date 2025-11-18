#ifndef BUSCALARGURA_H
#define BUSCALARGURA_H

#include "operacoes.h"

struct lista {
    int inicio;
    int qnt;
    char **atributos;
};

struct lista* criaLista(char *atr);

void insereLista(struct lista *l, char *atr);

unsigned char listaVazia(struct lista *l);

char *devolveItemLista(struct lista *l);

void liberaLista(struct lista *l);

void buscaLargura(struct listaDependencias *lista, char* atr);

#endif
