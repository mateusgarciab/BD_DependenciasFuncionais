#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista {
    int inicio;
    int qnt;
    char **atributos;
};

struct lista* criaLista(char *atr) {
    struct lista *l = malloc(sizeof(struct lista));
    l->inicio = 0;
    l->qnt = 0;
    l->atributos = malloc(sizeof(char*) * 100);
    int nAtr = strlen(atr);
    for (int i = 0; i < nAtr; i++) {
        l->atributos[i] = malloc(sizeof(char) * 2);
        l->atributos[i][0] = atr[i];
        l->atributos[i][1] = '\0';
        l->qnt++;
    }

    return l;
}

int comparaAtributos(const void *a, const void *b) {
    return (*(char*)a - *(char*)b);
}

void insereLista(struct lista *l, char *atr) {
    printf("Inserindo %s na lista\n", atr);
    qsort(atr, strlen(atr), sizeof(char), comparaAtributos);
    for (int i = l->inicio; i < l->qnt; i++) {
        if (strcmp(l->atributos[i], atr) == 0)
            return;
    }

    l->atributos[l->qnt] = malloc(sizeof(char) * (strlen(atr) + 1));
    strcpy(l->atributos[l->qnt], atr);
    
    
    l->qnt++;
}

unsigned char listaVazia(struct lista *l) {
    unsigned char vazio;
    if (l->qnt == 0)
        vazio = 1;
    else
        vazio = 0;
    return vazio;
}

char *devolveItemLista(struct lista *l) {
    if (listaVazia(l))
        return NULL;

    l->qnt--;
    return l->atributos[l->inicio++];
}

void liberaLista(struct lista *l) {
    for (int i = 0; i < l->qnt; i++) {
        free(l->atributos[i]);
    }
    free(l->atributos);
    free(l);
}


void buscaLargura() {

}

int main() {
    char atributos[] = "ABCDEF";
    struct lista *l = criaLista(atributos);

    char *letra = malloc(sizeof(char) * 10);
    letra[0] = 'G';
    letra[1] = '\0';
    insereLista(l, letra);
    letra[0] = 'B';
    letra[1] = 'A';
    letra[2] = '\0';
    insereLista(l, letra);
    letra[0] = 'A';
    letra[1] = 'B';
    insereLista(l, letra);
    /* insereLista(l, "CDE");
    insereLista(l, "CBD");
    insereLista(l, "CDAFEB");
    insereLista(l, "A");
    insereLista(l, "F");
    insereLista(l, "EF");
    insereLista(l, "BA"); */

    printf("%d %d\n", l->inicio, l->qnt);
    printf("Atributos na lista:\n");
    for (int i = 0; i < l->qnt - l->inicio; i++) {
        printf("%s\n", l->atributos[i]);
    }

    char *item;
    while (!listaVazia(l)) {
        item = devolveItemLista(l);
        printf("Item removido: %s %d %d\n", item, l->inicio, l->qnt);
    }


    liberaLista(l);
    return 0;
}