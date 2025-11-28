#ifndef LISTA_BUSCALARGURA_H
#define LISTA_BUSCALARGURA_H

#include "operacoes.h"

struct lista {
    int inicio;
    int qnt;
    int total_alocado;
    char **atributos;
};

//Cria uma lista e devolve o ponteiro para ela
struct lista* criaLista(char *atr);

//Utilizada para o uso do qsort
int comparaAtributos(const void *a, const void *b);

//Insere um atributo na lista
void insereLista(struct lista *l, char *atr);

//Verifica se a lista esta vazia
unsigned char listaVazia(struct lista *l);

//Devolve um item da lista
char *devolveItemLista(struct lista *l);

//Libera lista da memória
void liberaLista(struct lista *l);

//Verifica se um atributo ou conjunto de atributos é chave
int ehChave(struct listaDependencias *lista, char *item, char *atr);

//Verifica se um atributo faz parte de uma chave
int fazParteChave(char letra, char *item);


#endif
