/* Andre Eiki Hiratsuka RA: 156263 turma IB - prof Regina */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define max 1000 
//bibliotecas

int verifica_nota(); //declara a funcao
int verifica_RA();


int auxIndex = 0; //variavel global que sera usada posteriormente
int auxEstado = 0;

//estrutura da arvore
//em vez de apenas 'info' dos slides, tem RA, as 3 notas, o nome e a media
typedef struct arv {
  int RA;
  char nome[max];
  int n1;
  int n2;
  int n3;
  int media;
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

//funcao insereABB do slide, porem ao inves de ser um char c, eh um PArv no, ja que existem inumeras informacoes
PArv insereABB(PArv arv, PArv no){
  PArv novo;
  if(arv == NULL){ //arvore vazia
    return no;
  } else if(no->RA < arv->RA){
      arv->esq = insereABB(arv->esq, no);
    } else {
        arv->dir = insereABB(arv->dir, no);
      }
  return arv;
}

//funcao de busca do slide, mas usando int em vez de PArv
int buscaABB(PArv arv, int c){
  if(arv == NULL){
    return 0;
  } else if(c<arv->RA) {
      return buscaABB(arv->esq, c);
    } else if(c>arv->RA){
        return buscaABB(arv->dir, c);
      } else if(c == arv->RA){
          return 1;
        }
  return 0;

}


//funcao retira adaptada na monitoria para que funcione no código
PArv retira(PArv r, int v)
{
    PArv t, pai, f;
    if (r == NULL)

        return NULL; // nao encontrou a chave
    else if (v < r->RA)

        r->esq = retira(r->esq, v);

    else if (r->RA < v)

        r->dir = retira(r->dir, v);

    else
    { // achou o elemento
        if (r->esq == NULL && r->dir == NULL)
        {

            // elemento sem filhos
            free(r);
            r = NULL;
        }
        else if (r->esq == NULL)
        {
            // só tem filho à direitaeita
            t = r;
            r = r->dir;
            free(t);
        }
        else if (r->dir == NULL)
        {
            // só tem filho à esquerdauerda
            t = r;
            r = r->esq;
            free(t);
        }
        else
        { // tem os dois filhos

            pai = r;
            f = r->esq;
            while (f->dir != NULL)
            {
                // busca o maior aa esquerdauerda
                pai = f;
                f = f->dir;
            }
            // troca as informações
            r->RA = f->RA;
						r->media = f->media;
						strcpy(r->nome, f->nome);
						r->n1 = f->n1;
						r->n2 = f->n2;
						r->n3 = f->n3;
						
            if (pai == r) // quando o pai do
                pai->esq = f->esq;

            else

                pai->dir = f->esq;

            free(f);
        }
        return r;
    }
  return r;
}

//funcao para opcao 1
PArv opcao_1(PArv tree){
  int RA, n1 = 11, n2 = 11, n3 = 11, media;
  char ra[max], N1[max], N2[max], N3[max];
  char nome[max];

	PArv no = (PArv)malloc(sizeof(TArv)); //em vez de alocar memoria na funcao insere, aloca-se aqui.
  getchar();
  printf("\nInsira a RA do aluno: "); //inserçao do RA 
  fgets(ra, 1000, stdin);
  ra[strcspn(ra, "\n")] = 0;
  verifica_RA(ra, RA);
  RA = strtol(ra, NULL, 10);
  while((verifica_RA(ra, RA) == 1) || buscaABB(tree, RA) == 1){ //verificacao. verifica se o RA foi digitado corretamente e nao foi digitado o mesmo RA antes
    printf("\nInsira o RA corretamente: ");
    fgets(ra, 1000, stdin);
    ra[strcspn(ra, "\n")] = 0;
    verifica_RA(ra, RA);
    RA = strtol(ra, NULL, 10);
  }
  no->RA = RA;

//insercao do nome
  printf("\nInsira o nome do aluno: ");
  fgets(nome, 1000, stdin);
  nome[strcspn(nome, "\n")] = 0;
  strcpy(no->nome, nome);

//insercao da nota 1
  printf("\nInsira a nota 1: ");
  fgets(N1, 1000, stdin);
  N1[strcspn(N1, "\n")] = 0;
  while(verifica_nota(N1, n1) == 1){
    printf("Digite a nota corretamente: ");
    fgets(N1, 1000, stdin);
    N1[strcspn(N1, "\n")] = 0;
  }
  n1 = strtol(N1, NULL, 10);
  no->n1 = n1;

//insercao da nota 2
  printf("\nInsira a nota 2: ");
  fgets(N2, 1000, stdin);
  N2[strcspn(N2, "\n")] = 0;
  while(verifica_nota(N2, n2) == 1){
    printf("Digite a nota corretamente: ");
    fgets(N2, 1000, stdin);
    N2[strcspn(N2, "\n")] = 0;
  }
  n2 = strtol(N2, NULL, 10);
  no->n2 = n2;

//insercao da nota 3
  printf("\nInsira a nota 3: ");
  fgets(N3, 1000, stdin);
  N3[strcspn(N3, "\n")] = 0;
  while(verifica_nota(N3, n3) == 1){
    printf("Digite a nota corretamente: ");
    fgets(N3, 1000, stdin);
    N3[strcspn(N3, "\n")] = 0;
  }
  n3 = strtol(N3, NULL, 10);
  no->n3 = n3;
  //verificar cada um: 
  media = (n1 + n2 + n3)/(float)3;
  no->media = media;

  tree = insereABB(tree, no); //inserir na arvore
  printf("\nNovo aluno inserido com sucesso!\n");
  return tree;
}
//funcao da opcao 2. essa funcao eh parecida com o exercicio 7 de aed, ja que pedem a mesma coisa.
void opcao_2(PArv tree, int altura){
    int i;

    //se o no for vazio
    if(tree == NULL){
        return;
    }

    //vai para a direita da arvore, aumentando a altura em 1 sempre que acontece isso
    opcao_2(tree->dir, altura+1);

    for(i=0; i<altura; i++){
        printf("\t");
    }

    printf("%d\n", tree->RA);
    opcao_2(tree->esq, altura+1); 
}
//funcao opcao 3
void opcao_3(PArv tree){
  if(tree !=NULL){ //ve se a arvore nao esta vazia
    if(tree->media < 6){ //se a media for menos que 6, printa os dados
      printf("\nRA: %d", tree->RA);
      printf("\nNome: %s", tree->nome);
      printf("\nNota 1: %d", tree->n1);
      printf("\nNota 2: %d", tree->n2);
      printf("\nNota 3: %d", tree->n3);
      printf("\nMedia: %d\n\n", tree->media);
      auxEstado = 1;
    }
    opcao_3(tree->esq); //vai recursivamente para os nos da esquerda e direita
    opcao_3(tree->dir);
  }
} 
//verifica se a nota digitada nao apresenta nenhum erro
int verifica_nota(char s[max], int n){
  int i;
  for(i=0; i<strlen(s); i++){
    if(isdigit(s[i]) == 0){
      return 1;
    }
  }
  n = strtol(s, NULL, 10);
  if(n > 10 || n < 0){
    return 1;
  }

  return 0;
}

//verifica se o RA digitado nao apresenta nenhum erro
int verifica_RA(char s[max], int n){
  int i;
  for(i=0; i<strlen(s); i++){
    if(isdigit(s[i]) == 0){
      return 1;
    }
  }
  n = strtol(s, NULL, 10);
  if(n < 1){
    return 1;
  }
  return 0;
}

//cria-se um vetor que armazena os RA que foram reprovados para que sejam removidos depois
void remove_reprovado(PArv a, int vetor[max]){
    if(a != NULL){
      remove_reprovado(a->esq, vetor);
      remove_reprovado(a->dir, vetor);
    if (a->media < 6){
      vetor[auxIndex++] = a->RA;
    }
  }
}
//funcao da opcao 4
PArv opcao_4(PArv tree){
  int vetor[max];
  int i, aux=1;
  remove_reprovado(tree, vetor);

  for(i=0; i<auxIndex; i++){ //apos o vetor, retira-se cada RA da arvore
	  tree = retira(tree, vetor[i]);
  }
	auxIndex = 0;


  printf("Encontrando os alunos reprovados...\n\nRemovendo...\n\nConcluido.\n");
  return tree;
}

void mostra_RA(); //declara a funcao

//funcao opcao 5
void opcao_5(PArv tree){
  char RA[1000];
  int ra;
  printf("\n\nDigite o RA que gostaria de avaliar: "); //pede o RA
  getchar();
  fgets(RA, 1000, stdin);
  RA[strcspn(RA, "\n")] = 0;
  verifica_RA(RA, ra);
  ra = strtol(RA, NULL, 10);
  while(verifica_RA(RA, ra) == 1){ //verifica o RA
      printf("\nInsira o RA corretamente: ");
      fgets(RA, 1000, stdin);
      RA[strcspn(RA, "\n")] = 0;
      verifica_RA(RA, ra);
      ra = strtol(RA, NULL, 10);
    }
  printf("\nOs alunos com RA menor que o solicitado sao:\n");
  mostra_RA(tree, ra);
	if(auxEstado == 0){
    printf("\nNao ha nenhum aluno com RA menos ou igual ao escolhido.\n\n");
	}
	auxEstado = 0;
}
//funcao complementar da opcao 5
void mostra_RA(PArv tree, int RA){
  if(tree == NULL){
    return;
  } else if(RA >= tree->RA){ //verifica se o RA do no eh menor ou igual ao RA do usuario
			auxEstado = 1;
      printf("\nRA: %d", tree->RA);
      printf("\nNome: %s", tree->nome);
      printf("\nNota 1: %d", tree->n1);
      printf("\nNota 2: %d", tree->n2);
      printf("\nNota 3: %d", tree->n3);
      printf("\nMedia: %d\n\n", tree->media);
      mostra_RA(tree->esq, RA);
      if(tree->dir != NULL){ //passa recursivamente mas sem verificar a arvore inteira, otimizando o processo
        if(RA >= tree->dir->RA) {
          mostra_RA(tree->dir, RA);
        }
      }
    } else if(RA < tree->RA){
        mostra_RA(tree->esq, RA);
      }

}
//funcao para liberar a memoria alocada
PArv opcao_6_7(PArv a){
  a = libera(a);
  return a;
}

char c; //para nao dar erro no switch case no 'default'
//funcao menu
void menu(PArv tree){
  int n=0;
  while(n != 7){
    printf("\nInsira o que deseja fazer: ");
    printf("\n1) Inserir um aluno na árvore: ");
    printf("\n2) Imprimir a árvore atual: ");
    printf("\n3) Mostrar os dados dos alunos que foram reprovados: ");
    printf("\n4) Excluir da árvore todos os alunos que foram reprovados: ");
    printf("\n5) Mostrar todos os alunos com chave menor ou igual a um dado RA: ");
    printf("\n6) Iniciar uma nova árvore: ");
    printf("\n7) Sair: \n\n");
    scanf("%d", &n);
    switch(n){ 
      case 1:
        tree = opcao_1(tree);
        break;
      case 2: 
        if(tree != NULL){
					printf("\nA arvore sera da seguinte estrutura:\n\n");
					opcao_2(tree, 0);
				}
				else{
					printf("\n\nArvore Vazia!\n\n");
				}
        break;
      case 3:
        printf("\n\nOs alunos reprovados sao: \n");
        opcao_3(tree);
        if(auxEstado == 0){
          printf("\nNao ha nenhum aluno reprovado.\n\n");
	      }
	      auxEstado = 0;
        break;
      case 4:
       	tree = opcao_4(tree);
        break;

      case 5: 
        opcao_5(tree);
        break;
      case 6:
        tree = opcao_6_7(tree);
        printf("\n\nDeletando...\n\nIniciando uma nova arvore...\n\nConcluido\n");
        break;

      case 7: 
        tree = opcao_6_7(tree);
        return;
      default:
        printf("\nEscolha um numero apropriadamente!\n");
        while((c = getchar()) != '\n' && c != EOF);
    }

  }
}


int main(void) {
  PArv tree = NULL;
  menu(tree);
  printf("\n\nFinalizando o programa...\n");
  return 0;
  }