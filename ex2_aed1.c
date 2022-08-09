/* André Eiki Hiratsuka RA: 156263 turma IB - prof Regina */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct  {
    char produto[20];
    int quantidade;
    int mes;
    char qm_comprou[20];
} cliente;
//vetor


void menu(); //declaracao

void opcao_1(int n, cliente* p) { //funcao para a opcao1
    int mes, i=0, soma=0;
    printf("\n\nQual e o mes que gostaria de procurar?\n ");
    scanf("%d", &mes);
    for (i=0; i<n; i++) {
        if (mes == (p+i)->mes) {
            soma = soma + (p+i)->quantidade; //somando a quantidade no mes escolhido
        }
    }
    printf("O total de produtos no mes %d e: %d\n", mes, soma);

    menu(p, n);
    return;
}
void opcao_2(int n, cliente* p) {
    int i=0, mes=0, soma=0;
    char produto[20], cliente[20];
    printf("\n\nQual e o mes? \n");
    scanf("%d", &mes);
    printf("Qual e o produto?\n");
    scanf("%s", produto);
    printf("Qual e o cliente?\n");
    scanf("%s", cliente);
    for (i=0; i<n; i++) {
        if (mes == (p+i)->mes) {
            if (strcmp((p+i)->produto, produto)==0){
                if (strcmp((p+i)->qm_comprou, cliente)==0) {
                    soma = soma + (p+i)->quantidade; //fazendo a soma nas especificacoes escolhidas
                }
            }
        }
    }
    printf("a soma dos produtos foi: %d", soma);
    menu(p, n);
    return;
}

void opcao_3(int n, cliente* p) { //faz a soma de todas as compras
    int soma=0, i=0, z=0, x=0;
    for (i=0; i<n; i++) {
        soma = 0;
        x = 0;
        for (z=0; z<i; z++) {
            if(strcmp((p+i)->produto, (p+z)->produto) == 0) {
                x = 1;
                break;
            }
         }
        if(x == 0){
            for(z=0; z<n; z++){
                if(strcmp((p+i)->produto, (p+z)->produto) == 0) {
                    soma = soma + (p+z)->quantidade;
                }
            }
            printf("\nProduto: %s     Quantidade: %d", (p+i)->produto, soma);
        }

    }

    menu(p, n);
    return;
}

void opcao_4(int n, cliente* p) { //encontra no vetor quem comprou e acessa quanto comprou
    int soma=0, i=0, z=0;
    for (i=0; i<n; i++) {
        soma = 0;
        for (z=0; z<i; z++) {
            if(strcmp((p+i)->qm_comprou, (p+z)->qm_comprou) == 0) {
                break;
            }
         }
        if(strcmp((p+i)->qm_comprou, (p+z)->qm_comprou) != 0){
            for(z=0; z<n; z++){
                soma = soma + (p+z)->quantidade;
            }
            printf("\nProduto: %s     Quantidade: %d", (p+i)->qm_comprou, soma);
        }

    }

    menu(p, n);
    return;
}


void menu(cliente* p, int n) { //funcao menu e switch case para cada opcao
    int menu=0;
    while (menu!=5) {
        printf("\nDigite o que gostaria de fazer: \n 1 Total de vendas num dado mes (de todos os produtos) \n 2 Total de vendas de um determinado produto num dado mes para um determinado cliente (qual produto, para quem e em que mes) \n 3 Total de vendas de cada produto (em todos os meses) \n 4 Total vendido para cada cliente \n 5 para sair\n");
        scanf("%d", &menu);
        switch (menu) {
            case 1:
                opcao_1(n, p);
                return;
            case 2:
                opcao_2(n, p);
                return;
            case 3:
                opcao_3(n, p);
                return;
            case 4:
                opcao_4(n, p);
                return;
            case 5:
                
                printf("Voce saiu com sucesso");
                free(p);
                return;
            default:
                printf("\nEssa nao e uma opcao valida");

        }
            
    }

}


int main() { //iniciando com os cadastros e fazendo a alocacao dinamica com aritmetica de ponteiros
    cliente *p;
    int n=0, i=0;
    printf("Digite quantos elementos tem o vetor:\n ");
    scanf("%d", &n);
    p = (cliente *)malloc(n * sizeof(cliente));
    for (i=0; i<n; i++) {
        printf("\nDigite seu nome:\n");
        scanf("%s", (p+i)->qm_comprou);
        printf("\nDigite o mes da compra:\n");
        scanf("%d", &(p+i)->mes);
        printf("\nDigite o produto:\n");
        scanf("%s", (p+i)->produto);
        printf("\nDigite a quantidade:\n");
        scanf("%d", &(p+i)->quantidade);
    }
    menu(p, n);


    return 0;
}