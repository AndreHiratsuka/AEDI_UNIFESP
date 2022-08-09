/* André Eiki Hiratsuka RA: 156263 turma IB - prof Regina */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct  {
    char marca[15];
    char modelo[25];
    int ano_fabricacao;
    char placa_carro[6];
    int quilometragem;
    int num_portas;
    char ar_condicionado;
} veiculos;

veiculos *veiculo[20];
//struct do cadastro

void entrada();

void opcao_1() { /* funcao para opcao1 */
  int p=0;
  FILE *arq;
  arq = fopen("carros.txt", "a+");
  if (arq == NULL){
    printf("Nao foi possível achar o arquivo");
  }
  printf("Em qual posicao de 1 a 20 deseja adicionar o veiculo que deseja?\n");
  scanf("%d", &p);
  if (p>20) {
    printf("por favor, coloque um numero de 1 a 20");
    scanf("%d", &p);
  }
  veiculo[p]=(veiculos*)malloc(sizeof(veiculos));


  struct veiculos; /* Pedindo o cadastro do novo veiculo*/
  printf("Digite a marca do veiculo: \n");
  scanf("%s", veiculo[p]->marca);
  getchar();
  fprintf(arq, "%s\n", veiculo[p]->marca);

  printf("\nDigite o modelo do veiculo:\n");
  scanf("%s", veiculo[p]->modelo);
  getchar();
  fprintf(arq, "%s\n", veiculo[p]->modelo);

  printf("\nDigite o ano de fabricacao do veiculo: \n");
  scanf("%d", &veiculo[p]->ano_fabricacao);
  getchar();
  fprintf(arq, "%d\n", veiculo[p]->ano_fabricacao);

  printf("\nDigite a placa do veiculo: \n");
  scanf("%s", veiculo[p]->placa_carro);
  getchar();
  fprintf(arq, "%s\n", veiculo[p]->placa_carro);

  printf("\nQual a quilometragem do carro: \n");
  scanf("%d", &veiculo[p]->quilometragem);
  fprintf(arq, "%d\n", veiculo[p]->quilometragem);

  printf("\nDigite o numero de portas do carro: \n");
  scanf("%d", &veiculo[p]->num_portas);
  fprintf(arq, "%d\n", veiculo[p]->num_portas);

  printf("O carro tem ar condicionado? Apenas s ou n: \n");
  scanf("%s", &veiculo[p]->ar_condicionado);
  getchar();
  fprintf(arq, "%s\n", &veiculo[p]->ar_condicionado);

  fclose(arq);
  free(veiculo[p]);
  entrada();
  return;
}

void opcao_2() { /*funcao para opcao2*/
    int p=0, p2=-1, p3=0, cadastro=0, linhas=1, entrada2=0;
    char placa[6], aux[20];
    char c=0;
    FILE *arq;
    arq = fopen("carros.txt", "r");
    if (arq == NULL) {
      printf("Nao foi possivel abrir o arquivo");
    }
    FILE *arq2;
    arq2 = fopen("carros2.txt", "w");
    if (arq2 == NULL){
      printf("Não foi possível abrir o arquivo2");
    }
    printf("\n\nDigite a placa do carro: \n");
    scanf("%s", placa);
    while(fscanf(arq, "%s", aux) != EOF) { /*Encontrando qual cadastro e a placa */
        veiculo[p]=(veiculos*)malloc(sizeof(veiculos));
        strcpy(veiculo[p]->marca, aux);
        fscanf(arq, "%s", veiculo[p]->modelo);
        fscanf(arq, "%d", &veiculo[p]->ano_fabricacao);
        fscanf(arq, "%s", veiculo[p]->placa_carro);
        fscanf(arq, "%d", &veiculo[p]->quilometragem);
        fscanf(arq, "%d%*c", &veiculo[p]->num_portas);
        fscanf(arq, "%c%*c", &veiculo[p]->ar_condicionado);
          if (strcmp(veiculo[p]->placa_carro, placa)==0){
                p2 = p;
                p3 = 1;
          }
      p++;
    }

    rewind(arq);
    c = getc(arq);
    while(c!=EOF){
      if(c=='\n'){
        linhas++;
      }
      c = getc(arq);
    }
    rewind(arq);

    if (p3!=1) {
      printf("Nao existe um veiculo com essa placa");
      fclose(arq);
      fclose(arq2);
      remove("carros2.txt");

      entrada();
      return;
    }

  cadastro = linhas/7;
  for (p=0; p<cadastro; p++){ /* menu da alteracao */
    if (p==p2){
      while (entrada2!=7) {
        printf("Digite o que gostaria de alterar: \n1-Marca\n2-Modelo\n3-Ano de Fabricacao\n4-Quilometragem\n5-Numero de portas\n6-Ar condicionado\n7-Fim da alteracao\n");
        scanf("%d", &entrada2);
          switch (entrada2) {
            case 1:
              printf("\nQual a nova marca? ");
              scanf("%s", veiculo[p2]->marca);
              break;

            case 2:
              printf("\nQual o novo modelo? ");
              scanf("%s", veiculo[p2]->modelo);
              break;
            case 3:
              printf("\nQual o novo ano de fabricacao? ");
              scanf("%d", &veiculo[p2]->ano_fabricacao);
              break;

            case 4:
              printf("\nQual a nova quilometragem? ");
              scanf("%d", &veiculo[p2]->quilometragem);
              break;

            case 5:
              printf("\nQual o novo numero de portas? ");
              scanf("%d%*c", &veiculo[p2]->num_portas);
              break;

            case 6:
              printf("\nAinda ha ar condicionado? ");
              scanf("%c", &veiculo[p2]->ar_condicionado);
              break;
            case 7:
              printf("Fim da alteracao.\n");
              break;

            default:
              printf("opcao invalida\n");
          }
      }
    }
    fprintf(arq2, "%s\n", veiculo[p]->marca);
    fprintf(arq2, "%s\n", veiculo[p]->modelo);
    fprintf(arq2, "%d\n", veiculo[p]->ano_fabricacao);
    fprintf(arq2, "%s\n", veiculo[p]->placa_carro);
    fprintf(arq2, "%d\n", veiculo[p]->quilometragem);
    fprintf(arq2, "%d\n", veiculo[p]->num_portas);
    fprintf(arq2, "%c\n", veiculo[p]->ar_condicionado);
  }


  fclose(arq);
  fclose(arq2);
  rename("carros.txt", "lixo.txt"); /* passando as informacoes para outro arquivo e renomeando-os */
  rename("carros2.txt", "carros.txt");
  remove("lixo.txt");
  for (p=0; p<cadastro; p++) {
    free(veiculo[p]);
  }
  entrada();
  return; 
}

void opcao_3() { /*funcao para opcao3*/
    int p=0, p2=0, cadastro=0;
    char placa[6], aux[20];
    FILE *arq;
    arq = fopen("carros.txt", "r");
    if (arq == NULL) {
      printf("Nao foi possivel abrir o arquivo");
    }
    printf("\n\nDigite a placa do carro: \n");
    scanf("%s", placa);
  while(fscanf(arq, "%s", aux) != EOF) { /* Encontrando o cadastro */
    veiculo[p]=(veiculos*)malloc(sizeof(veiculos));
    strcpy(veiculo[p]->marca, aux);
    fscanf(arq, "%s", veiculo[p]->modelo);
    fscanf(arq, "%d", &veiculo[p]->ano_fabricacao);
    fscanf(arq, "%s", veiculo[p]->placa_carro);
    fscanf(arq, "%d", &veiculo[p]->quilometragem);
    fscanf(arq, "%d%*c", &veiculo[p]->num_portas);
    veiculo[p]->ar_condicionado = fgetc(arq);
    fgetc(arq);
    p2=1;
    if (p2!=1) {
      printf("Nao foi possivel achar o cadastro\n");
      entrada();
      return;
    }

    if (strcmp(veiculo[p]->placa_carro, placa)==0){ /*Printando os dados */
      printf("\nPlaca: %s\n", veiculo[p]->placa_carro);
      printf("Marca: %s\n", veiculo[p]->marca);
      printf("Modelo: %s\n", veiculo[p]->modelo);
      printf("Ano de Fabricacao: %d\n", veiculo[p]->ano_fabricacao);
      printf("Quilometragem: %d\n", veiculo[p]->quilometragem);
      printf("Numero de Portas: %d\n", veiculo[p]->num_portas);
      printf("Ar Condicionado: %c\n", veiculo[p]->ar_condicionado);
    }
    p++;
    cadastro++;

  }
  for (p=0; p<cadastro; p++) {
    free(veiculo[p]);
  }
  fclose(arq);
  entrada();
  return;
}

void opcao_4() { /* funcao para opcao4*/
    int p=0, p2=0, p3=0, cadastro=0, linhas=1;
    char placa[6], aux[20];
    char c=0;
    FILE *arq;
    arq = fopen("carros.txt", "r");
    if (arq == NULL) {
      printf("Nao foi possivel abrir o arquivo");
    }
    FILE *arq2;
    arq2 = fopen("carros2.txt", "w");
    if (arq2 == NULL){
      printf("Não foi possível abrir o arquivo2");
    }
    printf("\n\nDigite a placa do carro: \n");
    scanf("%s", placa);
    while(fscanf(arq, "%s", aux) != EOF) { /* Encontrando o cadastro */
        veiculo[p]=(veiculos*)malloc(sizeof(veiculos));
        strcpy(veiculo[p]->marca, aux);
        fscanf(arq, "%s", veiculo[p]->modelo);
        fscanf(arq, "%d", &veiculo[p]->ano_fabricacao);
        fscanf(arq, "%s", veiculo[p]->placa_carro);
        fscanf(arq, "%d", &veiculo[p]->quilometragem);
        fscanf(arq, "%d%*c", &veiculo[p]->num_portas);
        fscanf(arq, "%c%*c", &veiculo[p]->ar_condicionado);
          if (strcmp(veiculo[p]->placa_carro, placa)==0){
      p2 = p;
      p3 = 1;
          }
      p++;
    }
    if (p3!=1) {
      printf("Nao existe um veiculo com essa placa\n");
      fclose(arq);
      fclose(arq2);
      remove("carros2.txt");
      entrada();
      return;
    }
    rewind(arq);
    c = getc(arq);
    while(c!=EOF){
        if(c=='\n'){
        linhas++;
    }
    c = getc(arq);
  }
    rewind(arq);
      cadastro = linhas/7;
  for (p=0; p<cadastro; p++){
    if (p==p2){
      continue; /* Nao printando especificamente o cadastro */
    } else {
      fprintf(arq2, "%s\n", veiculo[p]->marca);
      fprintf(arq2, "%s\n", veiculo[p]->modelo);
      fprintf(arq2, "%d\n", veiculo[p]->ano_fabricacao);
      fprintf(arq2, "%s\n", veiculo[p]->placa_carro);
      fprintf(arq2, "%d\n", veiculo[p]->quilometragem);
      fprintf(arq2, "%d\n", veiculo[p]->num_portas);
      fprintf(arq2, "%c\n", veiculo[p]->ar_condicionado);

    }
  }

  fclose(arq);
  fclose(arq2);
  rename("carros.txt", "lixo.txt");
  rename("carros2.txt", "carros.txt");
  remove("lixo.txt");
  
  printf("Voce apagou com sucesso esse cadastro");
  for (p=0; p<cadastro; p++) {
    free(veiculo[p]);
  }
  entrada();
  return;
}

void menu_opcao_2() {

}

void entrada() {
    int entrada=0;
    while (entrada!=5) {
        printf("\nDigite o que gostaria de fazer: \n 1 para novo cadastro de veiculo \n 2 para alterar cadastro \n 3 mostrar os dados de um veiculo \n 4 para apagar registro \n 5 para sair\n");
        scanf("%d", &entrada);
        switch (entrada) {
            case 1:
                opcao_1();
                return;
            case 2:
                opcao_2();
                return;
            case 3:
                opcao_3();
                return;
            case 4:
                opcao_4();
                return;
            case 5:
                
                printf("Voce saiu com sucesso");
                return;
        }
    }

}
//switch case para cada opcao

int main(void) {
    entrada();
return 0;
}