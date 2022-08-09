/* Andre Eiki Hiratsuka RA: 156263 turma IB - prof Regina */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define max 1000

typedef struct lista { //struct da lista
    char info;
    struct lista* prox;
} TLista;
typedef TLista *PLista;

PLista inicializa_lista() { //inicializa uma lista
    return NULL;
}

/*insercao no inicio: retorna a lista atualizada*/
PLista insere(PLista ultimo, char val){
    PLista novo = (PLista)malloc(sizeof(TLista));
    novo->info=val;
    if (ultimo==NULL){
        ultimo = novo;
        novo->prox=novo;
    }
    else {
        novo->prox = ultimo->prox;
        ultimo->prox = novo;
    }
    return ultimo;
}

void libera(PLista ultimo){ //libera a memoria
    PLista p = ultimo->prox;
    PLista q = ultimo;
    while(p!=ultimo){
        q = p;
        p=p->prox;
        free(q);
    }
    free(ultimo);
}

int verificacao(char s[]){ //verifica se tem algo alem de numero na string
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

int verifica_letra(char s[]){ //verifica se tem algo alem de letra na string
        int aux = 0;

    if(strlen(s) > 50){ //verifica se tem mais de 50 caracteres
        return 1;
    }

    for (int i = 0; s[i] != '\0'; i++) {
        if(s[i] == '\n'){
            continue;
        }
        aux=1;
        if (isalpha(s[i]) == 0){ //verifica se e letra
            return 1;
        }
        if (isupper(s[i]) != 0){ //verifica se e minusculo
            return 1;
        }

    }

    //Verificacao caso o usuario nao digite nada
    if(aux == 0){
        return 1;
    }

    return 0;
}

int saida(PLista lc1, char sub[], int tamanho){
  int k, h;//auxiliadores no 'for'
  PLista i; //ponteiro 1
  PLista j; //ponteiro 2
  int pontuacao=0, contador=0;
  int tamanhosub = strlen(sub) - 1;
  j=lc1->prox;
  i=j;
  for (k = 0; k < tamanho; k++){
    contador = 0;
    for (h=(tamanhosub-1); h >= 0; h--){
        if(sub[h] == i->info){ //se os caracteres batem
            contador++;
        }
        i = i->prox;
    }
    if(contador == tamanhosub){ //verifica se todas as letras que coincidiram batem com o tamanho da substring
        pontuacao=1;
    }    
    j = j->prox;
    i = j;
    }

  if (pontuacao == 1){
    return 1;
  }
  else {
  return 0;
  }
}

int main(void){
    char n[max], l[max], sub[max];
    int num=0;
    PLista lc1 = inicializa_lista();
    printf("\nDigite o numero inteiro positivo: ");
    fgets(n, 1000, stdin);
    while (verificacao(n) == 1){ //verifica a string de numero
        printf("\nDigite corretamente o numero: \n");
        fgets(n, 1000, stdin);
    }
    num = atoi(n); //transforma a string em int
    printf("\nAgora digite um anagrama qualquer de ate 50 letras minusculas: ");
    fgets(l, 1000, stdin);
    while (verifica_letra(l) == 1){ //verifica a string de letra
        printf("\nDigite corretamente o anagrama: \n");
        fgets(l, 1000, stdin);
    }

    int i=0;
    while (i<(strlen(l)-1)){ //insere a string l1 pra lista circular
        lc1 = insere(lc1, l[i]);
        i++;
    }
    printf("\nDigite agora as %d substrings (uma por linha e todas com letras minusculas): \n", num);
    int menor=0, pontuacao=0, contagem = 0;
    for (i=0; i<num; i++){
      fgets(sub, 1000, stdin);
      while (verifica_letra(sub) == 1){ //verifica a string de letra
        printf("\nDigite corretamente o anagrama %d: \n", i);
        fgets(sub, 1000, stdin);
      }
      pontuacao = saida(lc1, sub, strlen(l) - 1); //retornando 1 ou 0, se a string deu zero ele add na pontuacao
      if(pontuacao == 1){ //se deu certo, add o menor numero para o int 'menor'
        contagem++; //variavel para numero de string ciclicas
        if(menor==0){ //se ainda nao teve uma substring coincidente
          menor = strlen(sub)-1;
        }
        else{
          if(strlen(sub)-1< menor){ //compara o tamanho da substring antiga com a nova
            menor = strlen(sub)-1;
          }
        }
      }

    }
    printf("\n\nNumero de strings ciclicas: %d \n\n", contagem);
    printf("Menor pontuacao: %d", menor);
    printf("\n\n");
    libera(lc1);
    return 0;
}