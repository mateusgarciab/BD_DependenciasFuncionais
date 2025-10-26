#ifndef OPERACOES_H
#define OPERACOES_H

struct Dependencia{
    char esquerda[26];
    char direita[26];
};

void calculaFecho(struct Dependencia *DF, int qtd, char *X);


#endif