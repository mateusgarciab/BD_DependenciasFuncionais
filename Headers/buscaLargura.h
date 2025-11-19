#ifndef BUSCALARGURA_H
#define BUSCALARGURA_H

#include "operacoes.h"

struct lista {
    int inicio;
    int qnt;
    char **atributos;
};

struct chaves {
    char **chave;
    int qtd;
};

struct lista* criaLista(char *atr);

void insereLista(struct lista *l, char *atr);

unsigned char listaVazia(struct lista *l);

char *devolveItemLista(struct lista *l);

void liberaLista(struct lista *l);

struct chaves *buscaLargura(struct listaDependencias *lista, char* atr);

int comparaAtributos(const void *a, const void *b);

#endif
