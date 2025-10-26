#ifndef LEARQUIVO_H
#define LEARQUIVO_H

/*
 * Função que devolve um ponteiro para o arquivo em modo de leitura.  
 */
FILE *devolveArquivo(char *nome);

char *devolveAtributos(FILE *arq);

char *devolveDependencias(FILE *arq);

#endif