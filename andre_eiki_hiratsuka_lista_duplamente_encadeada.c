/* Andre Eiki Hiratsuka RA: 156263 turma IB - prof Regina */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define max 1000

typedef struct lista2 { //struct da lista duplamente encadeada
    int expoente;
    int coeficiente;
    struct lista2* prox;
    struct lista2* ant;
} TLista2;
typedef TLista2 *PLista2;

PLista2 inicializa_lista() { //inicializa uma lista
    return NULL;
}

void menu(PLista2 lc1, PLista2 lc2); //declara a funcao

PLista2 insere_ordenado(PLista2 l, int v1, int v2){ //insere ordenado crescentemente. como e uma lista duplamente encadeada, pode ser usada como ordem decrescente tambem
    PLista2 aux, ant;
    PLista2 novo = (PLista2)malloc(sizeof(TLista2));
    novo->expoente = v1;
    novo->coeficiente = v2;
    if(l == NULL){ //sera o primeiro
    novo->ant = NULL;
    novo->prox = NULL;
    l = novo;
    } else{
        aux = l;
        while(aux->prox != NULL && aux->expoente<v1){
            aux = aux->prox;
        }
        if(aux->expoente<v1){ //insere novo no fim
            novo->prox = NULL;
            novo->ant = aux;
            aux->prox = novo;
        } else { //insere depois de aux
            novo->prox = aux;
            novo->ant = aux->ant;
            if(aux->ant!=NULL){ //se nao for o 1o no
                aux->ant->prox = novo;
            } else {
                l = novo; //atualiza inicio da lista
                novo->ant = NULL;
            }
            aux->ant = novo;
        }
    }
    return l;
}


PLista2 libera_lista(PLista2 lista){ //libera a memoria
    
		if(lista != NULL){
      libera_lista(lista->prox);
			free(lista);
    }

		return NULL;
}
/* verifica se o polinômio apresenta os requisitos para o código dar certo, como nao apresentar nenhuma letra alem de 'x', nao ter monomios com coeficiente igual a zero, expoente negativo etc */
int verificacao(char s[]){ 
    int aux = 0;
    int aux2 = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if(s[i] == ' '){
          return 1;
        }
        if(s[i] == '\n'){
            continue;
        }
        aux=1; 
    if(strlen(s) == 2){
      if(isdigit(s[0])){
        aux2 = 1;
      }
    } else if(strlen(s) == 3){
      if(s[0] == '-'){
        if(isdigit(s[1])){
          aux2 = 1;
        }
      }
    }
    if(s[i] == '^'){
      if(s[i+1] == '-'){
        return 1;
      }
    }
        if(isalpha(s[i])){
          if (s[i] == 'x' || s[i] == '^' ){
            aux2 = 1;
          } else {
              return 1;
          }
        }
    }

    //Verificacao caso o usuario nao digite nada
    if(aux == 0){
        return 1;
    }
    if(aux2 == 0){ //caso haja monomio, retorna errado
      return 1;
    }

//verificacao caso o usuario nao digite um polinomio com coef maior que 0:
if(aux2 == 0){
  return 1;
}
return 0;

}
//funcao que facilita na hora de inserir na lista. ex: 3x vira +3x^1
//verifica todas as possibilidades que nao sejam da forma ax^n, como expoente elevado a 1 ou 0, coeficiente igual a 1 ou 0 etc
int polinomio(char p[max], PLista2 *lc){
  int i=0;
	PLista2 lista = *(lc);
  int contador = 0; //conta qual posiçao da string poli
  char poli[max], anterior = 'x'; //string auxiliar, que recebera o polinomio mais facil de inserir na lista
  for(i=0; i<strlen(p); i++){
    if(i == 0){ //se for o primeiro elemento
      if(p[i] == '-'){ //se o coeficiente for negativo
        poli[contador] = '-';
        contador++;
        anterior = '+';
      } else { //se for positivo
          poli[contador] = '+';
          contador++;
          anterior = '+';
        }
      if(p[i] == 'x'){ //se n tiver um numero na frente do x, coeficiente = 1
        poli[contador] = '1';
        contador++;
        poli[contador] = 'x';
        contador++;
				if(p[i+1] == '\n'){ //se n tiver '^', expoente = 1
					poli[contador] = '^';
        	contador++;
        	poli[contador] = '1';
        	contador++;
				}
      }
			if(isdigit(p[i]) != 0) { //se for um numero, expoente = 0
          poli[contador] = p[i];
          contador++;
          if(p[i+1] == '\n'){
            poli[contador] = 'x';
            contador++;
            poli[contador] = '^';
            contador++;
            poli[contador] = '0';
            contador++;
          }
        }
    } else { //se nao for o primeiro elemento
        if(p[i] == '+' || p[i] == '-'){ //quando for um operador
          poli[contador] = p[i];
          contador++;
		  anterior = '+';
            if(p[i+1] == 'x'){ //se nao houver um numero antes de x, coeficiente = 1
              poli[contador] = '1';
              contador++;
            }
        } else if(p[i] == 'x'){ //quando for um x
            poli[contador] = p[i];
            contador++;
						anterior = 'x';
            if(p[i+1] != '^'){ //quando n houver '^', expoente = 1
              poli[contador] = '^';
              contador++;
              poli[contador] = '1';
              contador++;
            }
          }
		  else if(anterior == '+' && (p[i+1] == '+' || p[i+1] == '-' || p[i+1] == '\n')){ //quando e um numero, expoente = 0
						poli[contador] = p[i];
            contador++;
		    		poli[contador] = 'x';
            contador++;
            poli[contador] = '^';
            contador++;
            poli[contador] = '0';
            contador++;
          } else{
            poli[contador] = p[i];
						contador++;
          }
      }
  }
  poli[contador] = '\0'; 


	int coeficiente, expoente, aux;
	char operador;
	char *paux = poli;
	while(sscanf(paux, "%c%d%*c%*c%d%n", &operador, &coeficiente, &expoente, &aux) == 3){
		paux += aux;
		printf("Operador: %c coeficiente: %d Expoente: %d\n", operador, coeficiente, expoente);

		if(coeficiente != 0){
      if(operador == '-'){ //se o operador = '-', inverte o sinal do coeficiente para inserir
        coeficiente = coeficiente*(-1);
      }
      lista = insere_ordenado(lista, expoente, coeficiente);
		}
  }
  printf("%s", poli);

	if(lista == NULL){ //se o coeficiente e = 0, nao havera insercao e a lista sera nula, retornando errado
		return 1;
  }

	*lc = lista;
	return 0;
}

int opcao_1(PLista2* lc1, PLista2* lc2){ //funcao da opcao 1, maior parte da funcao esta em verificacao() e polinomio()
//a funcao opcao_1() pede o polinomio do usuario para as outras funcoes executarem corretamente
  *lc1 = libera_lista(*lc1); //libera uma vez caso queira inserir de novo
  *lc2 = libera_lista(*lc2);
  char p1[max], p2[max];
  int i=0, j=0, aux = 0;
  PLista2 lcaux = inicializa_lista();
  printf("\n\nDigite o polinomio 1 sem espaços: ");
  fgets(p1, 1000, stdin);
  while(verificacao(p1)==1){
    printf("\nDigite o polinomio corretamente: ");
    fgets(p1, 1000, stdin);
  }
  if (polinomio(p1, lc1) == 1){
    printf("Digite um polinomio corretamente. Retornando ao inicio...\n\n");
		return 0;
  }
    printf("\n\nDigite o polinomio 2 sem espaços: ");
    fgets(p2, 1000, stdin);
    while(verificacao(p2)==1){
        printf("\nDigite o polinomio corretamente: ");
        fgets(p2, 1000, stdin);
    }
    if (polinomio(p2, lc2) == 1){
    printf("Digite um polinomio corretamente. Retornando ao inicio...\n\n");
		return 0;
    }
    printf("\nPolinomios salvos com sucesso!\n");
    return 0;
}
//como a lista ja esta ordenada, a funcao soma analisa os expoentes das duas listas, se lc1 ou lc2 sao maiores ou expoente e igual.
void opcao_2(PLista2 lc1, PLista2 lc2){ //funcao soma
  while(lc1->prox != NULL){  //lc = lc->prox faz com que analise os expoente decrescentemente com lc = lc->ant
		lc1 = lc1->prox;
	}
  while(lc2->prox != NULL){
		lc2 = lc2->prox;
	}
  printf("\nA soma e: ");
  do{ 
		if(lc1 == NULL && lc2 != NULL){ //analisa se uma das listas esta nula, ai printa a lista n/ nula
			do {
        printf("%dx^%d", lc2->coeficiente, lc2->expoente);
        lc2 = lc2->ant;
      } while(lc2 != NULL);
		}
		else if(lc1 != NULL && lc2 == NULL){
			do {
        printf("%dx^%d", lc2->coeficiente, lc2->expoente);
        lc2 = lc2->ant;
      } while(lc2 != NULL);
    }
		else{ //caso das duas n sejam nulas
      if(lc1->expoente > lc2->expoente){ //caso 1
          if(lc1->coeficiente < 0){ //operadores + ou -
            printf("-");
          } else if(lc1->coeficiente > 0) { 
              printf("+");
            }
          if(lc1->coeficiente == 1 && lc1->expoente == 1){ //coeficiente 1 e expoente 1
            printf("x");
          } 
          else if(lc1->coeficiente > 1 && lc1->expoente == 1){ //qqr coeficiente e expoente 1
            printf("%dx", lc1->coeficiente);
          }
          else if(lc1->coeficiente >= 1 && lc1->expoente > 1){ //expoente > 1
              printf("%dx^%d", lc1->coeficiente, lc1->expoente);
            }
        lc1 = lc1->ant;
      } else if(lc1->expoente < lc2->expoente){ //caso 2
          if(lc2->coeficiente < 0){ //logica do caso 1 se aplica ao caso 2
            printf("-");
          } else if(lc2->coeficiente > 0) {
              printf("+");
            }
          if(lc2->coeficiente == 1 && lc2->expoente == 1){
            printf("x");
          } else if(lc2->coeficiente >= 1 && lc2->expoente > 1){
              printf("%dx^%d", lc2->coeficiente, lc2->expoente);
            }
          lc2 = lc2->ant;
        } else if(lc1->expoente == lc2->expoente){ //caso 3
            int aux = lc1->coeficiente + lc2->coeficiente; //faz a soma
            if(aux < 0){ //analisa o sinal do coeficiente para printar o operador
              printf("-");
            } 
            else if(aux > 0) {
              printf("+");
            }
            else if(aux == 0){
              printf("0");
            }
            if(lc1->expoente == 1){ //analisa o expoente para printar do modo padrao
            printf("%dx", aux);
            } 
            else if(aux >= 1 && lc1->expoente > 1){
              printf("%dx^%d", aux, lc1->expoente);
            }
            else{
              printf("%d", aux);
            }
            lc1 = lc1->ant;
            lc2 = lc2->ant;
          }
    }
  } while(lc1 != NULL && lc2 != NULL);
}


void opcao_3(PLista2 lc1, PLista2 lc2){ //funcao subtracao. a logica e a mesma da funcao soma
  while(lc1->prox != NULL){
		lc1 = lc1->prox;
	}
  while(lc2->prox != NULL){
		lc2 = lc2->prox;
	}
  printf("\nA subtracao e: ");
  do{ 
    if(lc1->expoente > lc2->expoente){ //caso 1
      if(lc1->coeficiente < 0){
        printf("-");
      } else {
          printf("+");
        }
      if(lc1->coeficiente == 1 && lc1->expoente != 0){
        printf("x");
      } else if(lc1->coeficiente >= 1){
          printf("%d", lc1->coeficiente);
        }
      if(lc1->expoente == 0){

      } else if(lc1->expoente == 1){
          printf("x");
        } else {
            printf("x^%d", lc1->expoente);
          }
      lc1 = lc1->ant;

    } else if(lc1->expoente < lc2->expoente){ //caso 2
        if(lc2->coeficiente < 0){
          printf("-");
        } else {
          printf("+");
        }
        if(lc2->coeficiente == 1 && lc2->expoente != 0){
          printf("x");
        } else if(lc2->coeficiente >= 1){
            printf("%d", lc1->coeficiente);
          }
        if(lc2->expoente == 0){

        } else if(lc2->expoente == 1){
            printf("x");
          } else {
              printf("x^%d", lc2->expoente);
            }
        lc2 = lc2->ant;
        } else if(lc1->expoente == lc2->expoente){ //caso 3
            int aux = lc1->coeficiente - lc2->coeficiente; //unica diferenca entre a funcao soma e subtracao
            if(aux < 0){
              printf("-");
            } else if(aux > 0) {
                printf("+");
            }
            if(aux == 0){
              printf("+0");
            } else if(aux == 1 && lc1->expoente == 1){
              printf("x");
              } else if(aux >= 1 && lc1->expoente > 1){
                  printf("%dx^%d", aux, lc1->expoente);
                }
            lc1 = lc1->ant;
            lc2 = lc2->ant;
          }
  } while(lc1 != NULL && lc2 != NULL);
}
void opcao_4(PLista2 lc1, PLista2 lc2){ //funcao da derivada: escolhe qual polinomio que derivar, faz a regra do tombo e printa
  while(lc1->prox != NULL){  //para que a lista tenha os expoentes decrescentes
		lc1 = lc1->prox;
	}
  while(lc2->prox != NULL){
		lc2 = lc2->prox;
	}
  int n;
  printf("\nDigite se gostaria de derivar o polinomio 1 ou 2: ");
  scanf("%d", &n);
    switch(n){
    case 1:
      printf("\nA derivada do polinomio 1 e: ");
      do {
        lc1->coeficiente *= lc1->expoente; //regra do tombo
        lc1->expoente -= 1;
        if(lc1->expoente < 0){ 
          printf("+0");
          return;
        }
          if(lc1->coeficiente < 0){
            printf("-");
          } else {
            printf("+");
          }
        if(lc1->coeficiente == 1 && lc1->expoente != 0){
          printf("x");
        } else if(lc1->coeficiente >= 1){
            printf("%d", lc1->coeficiente);
          }
        if(lc1->expoente == 0){

        } else if(lc1->expoente == 1){
            printf("x");
          } else {
              printf("x^%d", lc1->expoente);
            }
        lc1 = lc1->ant;
      } while(lc1 != NULL);
			break;
		
		case 2:
        printf("A derivada do polinomio 2 e: ");
      do {
        lc2->coeficiente *= lc2->expoente; //regra do tombo
        lc2->expoente -= 1;
        if(lc2->expoente < 0){
          printf("0");
          return;
        }
          if(lc2->coeficiente < 0){
            printf("-");
          } else {
            printf("+");
          }
        if(lc2->coeficiente == 1 && lc2->expoente != 0){
          printf("x");
        } else if(lc2->coeficiente >= 1){
            printf("%d", lc1->coeficiente);
          }
        if(lc2->expoente == 0){

        } else if(lc2->expoente == 1){
            printf("x");
          } else {
              printf("x^%d", lc2->expoente);
            }
        lc2 = lc2->ant;
      } while(lc2 != NULL);
			break;
			
      default:
        printf("\nEscolha o polinomio corretamente: ");
    }
  }


void menu(PLista2 lc1, PLista2 lc2){ //funcao menu
  int i;
	do{
    printf("\n\nDigite o que gostaria de fazer: \n\n");
    printf("1- Inserir novos polinomios:\n");
    printf("2- Somar polinomios:\n");
    printf("3- Subtrair polinomios:\n");
    printf("4- Derivar um polinomio:\n");
    printf("5- Sair:\n\n\n");
			scanf("%d%*c", &i);
	  	switch (i) {
			case 1:
				opcao_1(&lc1, &lc2);
			break;
			case 2:
				opcao_2(lc1, lc2);
			break;
			case 3:
        opcao_3(lc1, lc2);
        break;
			case 4:
        opcao_4(lc1, lc2);
				break;
			case 5:
				printf("Saindo do programa...\n\n");
				libera_lista(lc1); //libera a memoria das listas quando sai
				libera_lista(lc2);
				break;
			default:
				printf("Opcao Invalida!!!!");
    	}
	}while(i!=5);

}


int main(){
    PLista2 lc1 = inicializa_lista(); //inicializa as listas e vai pro menu
    PLista2 lc2 = inicializa_lista();
    menu(lc1, lc2);
    return 0;
}