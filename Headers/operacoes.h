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

//Cria uma lista de dependencias separando as que estão do lado esquerdo e direito do ->
struct listaDependencias* devolveDependencia(char* dependencias);

//A partir da lista de dependências calcula o fecho de um atributo X
char *calculaFecho(struct listaDependencias *lista, char *X);

//A partir da lista de dependências calcula as três fases da cobertura mínima
void calcularCoberturaMinima(struct Dependencia *DF, int qtd);

//Gera uma lista de chaves candidatas a partir da lista de dependências e os atributos
struct chaves *buscaLargura(struct listaDependencias *lista, char* atr);

//Verifica se um atributo já está na lista de primos, usada para formasNormais
int jaEhprimo(char *primos, char atr, int tamPrimos);

//Verifica se o lado esquerdo está nas chaves, usada para formasNormais
int estaNasChaves(struct chaves *c, char *ladoEsquerdo);

//Verifica se as dependências estão em BCNF
char *ehBCNF(struct listaDependencias *l, struct chaves *c);

//Verifica se as dependências estão em 3FN
char *eh3FN(struct listaDependencias *l, struct chaves *c, char *primos)

//Verifica as formas normais 3FN e BCNF
void formasNormais(struct listaDependencias *l, char *atr);

#endif