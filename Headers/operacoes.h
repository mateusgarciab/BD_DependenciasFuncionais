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

struct chaves {
    char **chave;
    int qtd;
};

struct listaDependencias* devolveDependencia(char* dependencias);

char *calculaFecho(struct listaDependencias *lista, char *X);

void calcularCoberturaMinima(struct Dependencia *DF, int qtd);

struct chaves *buscaLargura(struct listaDependencias *lista, char* atr);

void formasNormais(struct listaDependencias *l, char *atr);

#endif