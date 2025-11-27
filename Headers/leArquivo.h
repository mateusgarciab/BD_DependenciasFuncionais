#ifndef LEARQUIVO_H
#define LEARQUIVO_H

//abre um arquivo e devolve o seu ponteiro
FILE *devolveArquivo(char *nome);

//Le os atributos do arquivo e filtra os caracteres necessários
char *devolveAtributos(FILE *arq);

//Le as dependências do arquivo e filtra os caracteres necessários
char *devolveStringDependencias(FILE *arq);

#endif