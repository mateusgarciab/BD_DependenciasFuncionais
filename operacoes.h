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

struct listaBFS{
    int qtd;
    char atributos[26];
};

struct listaDependencias* devolveDependencia(char* dependencias);

char *calculaFecho(struct listaDependencias *lista, char *X);

void calcularCoberturaMinima(struct Dependencia *DF, int qtd);

#endif