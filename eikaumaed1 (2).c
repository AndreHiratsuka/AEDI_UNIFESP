/* Andre Eiki Hiratsuka RA: 156263 turma IB - prof Regina */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define max 1000 
//bibliotecas


//estrutura da arvore
//dessa vez, existe um int variavel, que ira diferenciar quando eh um numero ou um operador. ele sera importante na hora de imprimir a arvore
typedef struct arv {
  char info;
  int variavel;
  struct arv* esq;
  struct arv* dir;
} TArv;
typedef TArv *PArv;

//libera a memoria alocada
PArv libera (PArv a){
    if (a!=NULL) {
        libera(a->esq); /* libera sae */
        libera(a->dir); /* libera sad */
        free(a); /* libera raiz */
    }
    return NULL;
}


PArv cria_raiz(int n, int variavel, PArv esq, PArv dir) {  // cria um nó alocando a memoria
    PArv p = (PArv) malloc(sizeof(TArv));
    p->info = n;
    p->variavel = variavel; //na funcao cria_arv faz com que: se for um operador, variavel = 1 
    p->esq = esq;
    p->dir = dir;
    return p;
}


//apos a criacao da string sem espacos em verificacao(), usa-se o sscanf para criar a arvore, visto que a string estara de uma forma uniforme. ex: 3  + 3 vira 3+3
PArv cria_arv(char s[]){
  int n1, n2, quantidade;
  char operador;
  char *aux;
  PArv tree = NULL;
  aux = s;

  if (3 == sscanf(aux, "%d%c%d%n", &n1, &operador, &n2, &quantidade)){

    tree = cria_raiz(operador, 1,cria_raiz(n1, 0, NULL, NULL), cria_raiz(n2, 0, NULL, NULL));

    aux += quantidade;
  } else {
    return NULL;
  }


  while (2 == sscanf(aux, "%c%d%n", &operador, &n1, &quantidade)){

    tree = cria_raiz(
      operador, 1, tree, cria_raiz(n1, 0, NULL, NULL)
    );

    aux += quantidade;
  }

  return tree;
}

//retorna 1 = erro
//retorna 0 = acerto
//nessa funcao, verifica-se todos os tipos de erro que a professora apontou no exercicio. alem disso, cria-se uma string sem as barras de espaço que o usuario possa ter digitado para facilitar a criacao da arvore.
int verificacao(char s[max]){
  int nulo, i;
  char s2[max];
  if(strlen(s)-1 > 500){ //caso tenha mais de 500 caracteres
    printf("\nMais de 500 caracteres!\n");
    return 1;
  }
  

int j=0;
  for(i=0; i<strlen(s); i++){ //transfere a string em outra sem as barras de espaço
    if(s[i] == ' '){
      continue;
    } else {
      s2[j] = s[i];
      j++;
      }
  }


  s2[j] = '\0';


  for(i=0; i<strlen(s); i++){ //analisando se tem 2 numeros seguidos separados apenas por espaço
    if(s[i] == ' '){
      j = i+1;
      int k = i-1;

      while(s[j] == ' '){
        j++;
      }
      while(s[k] == ' '){
        k--;
      }
      if(isdigit(s[j]) && isdigit(s[k])){
        printf("\nDois numeros seguidos!\n");
        return 1;
      }
    }
  }


  if(s2[0] == '\n'){ //verifica se a string esta vazia
    nulo = 0;
  } else {
    nulo = 1;
  }


  for(i=0; i<strlen(s2); i++){ //verificando se existe 2 operadores seguidos
    if(s2[i] == '+'){
      if(s2[i+1] == '+' || s2[i+1] == '-'){
        printf("\nDois operadores seguidos!\n");
        return 1;
      }
    }
    if(s2[i] == '-'){
      if(s2[i+1] == '+' || s2[i+1] == '-'){
        printf("\nDois operadores seguidos!\n");
        return 1;
      }
    }
  }


  if(s2[0] == '-'){ //verifica se comeca com numero negativo
    printf("\nNao comece com numero negativo!\n");
    return 1;
  }


  for(i=0; i<strlen(s2); i++){ //confere se tem apenas numeros ou operadores
    if((s2[i] >= 48 && s2[i] <= 57) || s2[i] == '+' || s2[i] == '-' ){
      continue;
    } else {
      printf("\nDigite apenas operadores ou numeros!\n");
      return 1;
    }
  }


  int contagem = 0;
  for(i=0; i<strlen(s2); i++){ //verifica se um numero tem mais de 10 digitos
    if(isdigit(s[i])){
      j = i;
      while(isdigit(s[j]) != 0){
        contagem++;
        j++;
      }
    }
    if(contagem>10){
      printf("\nExiste um numero com mais de 10 digitos!\n");
      return 1;
    }

  }

  if(nulo==0){ //se a string estiver vazia, retorna errado
    printf("\nString vazia!\n");
    return 1;
  }


  strcpy(s, s2); //copia a string sem espaço para a original
  return 0;//se nao estiver nada errado, retorna certo

  
}


//funcao para imprimir a arvore
void imprime_arv(PArv p, int altura){
    int i;

    if(p == NULL)
        return;

    imprime_arv(p->dir, altura+1);

    for(i=0; i<altura; i++) //utiliza-se o nivel para calcular quantos \t sao precisos para imprimir
        printf("\t");

    if (p->variavel == 1) { //a maior diferença da impressao de uma arvore binaria no exercicio 7 eh verificar se precisa imprimir um numero ou um operador, ou seja, %3c ou %3d
        printf("%3c\n",p->info);
    } else{
        printf("%3d\n",p->info);
    }

    imprime_arv(p->esq, altura+1); 
}

//funcao que faz a soma da arvore
//como a arvore tem nos majoritariamente para um lado, eh possivel ir arv->esq ate o final e ir somando o resto
int conta(PArv arv) {
  if(arv != NULL){ 
    if((arv->esq != NULL) && (arv->dir != NULL)){ //apenas operadores terao arv->esq e arv-> diferente de NULL. 
      if(arv->info == '-'){ //faz uma subracao
        return conta(arv->esq) - arv->dir->info;
      } else if(arv->info == '+') { //faz uma soma
          return conta(arv->esq) + arv->dir->info;
        }
    } else {
        return arv->info;
      } 
  }

  return 0;
}



int main(void) {
  char expressao[max];
  printf("Digite a expressao que deseja calcular: "); //pedindo a expressao
  fgets(expressao, 1000, stdin);
  expressao[strcspn(expressao, "\n")] = 0; //apaga o \n
  while(verificacao(expressao) == 1){ //ate a expressao estar correta, continuara nesse while. explicacao mais detalhada na propria funcao
    printf("Digite a expressao corretamente: ");
    fgets(expressao, 1000, stdin);
    expressao[strcspn(expressao, "\n")] = 0;
  }
  
  PArv tree = NULL;
  tree = cria_arv(expressao); //criacao da arvore

  printf("\n\nA arvore sera do seguinte formato: \n\n"); //impressao da arvore
  imprime_arv(tree, 0);

  int resultado;
  resultado = conta(tree); //soma da arvore
  printf("\n\nO resultado da expressao sera: %d.\n", resultado);

  tree = libera(tree); //liberand a memoria alocada
  return 0;
}