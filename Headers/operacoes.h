#ifndef OPERACOES_H
#define OPERACOES_H

struct listaDependencias{
    int qtd;
    struct Dependencia *DF;
};

struct Dependencia{
    char esquerda[26];
    char direita[26];
};

struct listaDependencias* devolveDependencia(char* dependencias);

void calculaFecho(struct listaDependencias *lista, char *X);


#endif