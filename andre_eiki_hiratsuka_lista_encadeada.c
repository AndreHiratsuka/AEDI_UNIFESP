/* Andre Eiki Hiratsuka RA: 156263 turma IB - prof Regina */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 1000

typedef struct lista { //struct da lista
    int info;
    struct lista* prox;
} TLista;
typedef TLista *PLista;


PLista inicializa_lista() { //inicializa a lista
    return NULL;
}

PLista insere(PLista l, int i) { //aloca a memoria para cada caractere
    PLista novo = (PLista)malloc(sizeof(TLista));
    novo->info = i;
    novo->prox = l;
    return novo;
}

void imprime (PLista l){ //imprime a soma
    /*variavel auxiliar para percorrer a lista */
    PLista p;
    printf("\nA soma e: ");
    for (p = l; p!=NULL; p = p->prox){
        printf("%d", p->info);
    }
    printf("\n");
}
void libera (PLista l){ //libera a memoria alocada
    PLista p = l, t;
    while (p != NULL){
        /*guarda referencia para o proximo elemento*/
        t = p->prox;
        free(p);
        p = t; //faz p apontar para o proximo
    }
}

int verificacao(char s[]){ //verifica se o que o usuario digitou esta correto
    int aux = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if(s[i] == '\n'){
            continue;
        }
        aux=1;
        if (isdigit(s[i]) == 0){
            return 1;
        }
    }

    //Verificacao caso o usuario nao digite nada
    if(aux == 0){
        return 1;
    }

    return 0;
}

void soma(PLista l1, PLista l2){ //funcao soma
    PLista lista1, lista2, l3 = inicializa_lista();
    int resto = 0, soma;
        for(lista1 =l1, lista2 = l2; lista1 != NULL && lista2 != NULL; lista1=lista1->prox, lista2=lista2->prox){
            soma = lista1->info + lista2->info + resto;
            if(soma>=10){
                resto = 1;
                l3 = insere(l3, soma - 10);
            } else {
                l3 = insere(l3, soma);
                resto = 0;
            }

        }
    if (resto == 1){
        l3 = insere(l3, resto);
    }

    imprime(l3);
    libera(l3);
}

int main(void){
    char n1[MAX], n2[MAX];
    int i=0;
    PLista l1 = inicializa_lista();
    PLista l2 = inicializa_lista();
    printf("\nDigite o numero 1: ");
    fgets(n1, 1000, stdin);
    while (verificacao(n1) == 1){
        printf("\nDigite corretamente o numero: \n");
        fgets(n1, 1000, stdin);
    }
    printf("\nDigite o numero 2: ");
    fgets(n2, 1000, stdin);
    while (verificacao(n2) == 1){
        printf("\nDigite novamente o numero: \n");
        fgets(n2, 1000, stdin);
    }

    if((strlen(n1)) > (strlen(n2))){  //verificacao para que as duas strings tenham o mesmo numero de algarismos, como 012 e 123
        int tamanho = strlen(n1) - strlen(n2);

        for(i=0; i<tamanho; i++){
            l2 = insere(l2, 0);
        }
    }
    else if((strlen(n1)) < (strlen(n2))){
        int tamanho = strlen(n1) - strlen(n2);

        for(i=0; i<tamanho; i++){
            l1 = insere(l1, 0);
        }
    }

    i=0;
    while (i<(strlen(n1)-1)){
        l1 = insere(l1, n1[i]-'0');
        i++;
    }
    i=0;
    while (i<(strlen(n2)-1)){
        l2 = insere(l2, n2[i]-'0');
        i++;
    }


    soma(l1, l2);
    libera(l1);
    libera(l2);
    return 0;
}