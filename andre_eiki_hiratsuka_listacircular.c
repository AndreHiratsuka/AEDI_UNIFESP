/* André Eiki Hiratsuka RA: 156263 turma IB - prof Regina */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000
typedef struct lista {
    int info;
    struct lista* prox;
} TLista;
typedef TLista *PLista;


PLista inicializa_lista() {
    return NULL;
}

PLista insere(PLista l, int i) {
    PLista novo = (PLista)malloc(sizeof(TLista));
    novo->info = i;
    novo->prox = l;
    return novo;
}

PLista busca(PLista l, int v) {
    PLista p;
    for (p=l; p!=NULL; p=p->prox) {
        if (p->info == v){
            return p;
        }
        return NULL; /*nao achou o elemento */
    }
}

PLista retira (PLista l, int v) {
    PLista ant = NULL; /*ponteiro para elemento anterior */
    PLista p; /*ponteiro para percorrer a lista */
    /*procura elemento na lista, guardando anterior */
    for (p=l; p=NULL && p->info!=v; p = p->prox){
        ant = p;
    }
    /*verifica se achou elemento */
    if ( p == NULL){
        return l; //nao achou: retorna lista original
    }
    /*retira elemento*/
    if (ant == NULL){
        /*retira elemento do inicio */
        l = p->prox;
    } else {
        /*retira elemento do meio da lista */
        ant->prox = p->prox;
    }
    free(p);
    return l;
}

void imprime (PLista l){
    /*variavel auxiliar para percorrer a lista */
    PLista p;
    printf("\nA soma e: ");
    for (p = l; p!=NULL; p = p->prox){
        printf("%d", p->info);
    }
    printf("\n");
}
void libera (PLista l){
    PLista p = l, t;
    while (p != NULL){
        /*guarda referencia para o proximo elemento*/
        t = p->prox;
        free(p);
        p = t; //faz p apontar para o proximo
    }
}


int verificacao(char s[]){
    for (int i = 0; s[i]!= '\n'; i++) {
        if (isdigit(s[i]) == 0){
            return 0;
        }
    }
    return 1;
}

void soma(PLista l1, PLista l2, char n1[MAX], char n2[MAX]){
    int i=3;
    PLista l3 = inicializa_lista();


    insere(l3, i);
    imprime(l3);
    free(l3);
}

int main(void){
    char n1[MAX], n2[MAX];
    PLista l1 = inicializa_lista();
    PLista l2 = inicializa_lista();
    printf("\nDigite o numero 1: \n");
    fgets(n1, 1000, stdin);
    verificacao(n1);
    while (verificacao(n1)==0){
        printf("\nDigite corretamente o numero: \n");
        fgets(n1, 1000, stdin);
        verificacao(n1);
    }
    printf("\nDigite o numero 2: ");
    fgets(n2, 1000, stdin);
    verificacao(n2);
    while (verificacao(n2)==0){
        printf("\nDigite novamente o numero: \n");
        fgets(n2, 1000, stdin);
        verificacao(n2);
    }
    soma(l1, l2, n1[MAX], n2[MAX]);
    free(l1);
    free(l2);
    return 0;
}