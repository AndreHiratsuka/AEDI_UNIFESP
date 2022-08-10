#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char marca[15], modelo[50], Placa_do_Carro[6], ar_condicionado;
    int ano_de_fabricacao, numero_de_portas, Quilometragem;
}Carro;
Carro *carros[20];

void opcao_um(Carro* carros){
  int i;

  FILE *arquivo;
  arquivo = fopen("carros.txt", "a+");
  
  if (arquivo == NULL){
      printf("Não foi possível achar o arquivo");
  }

  printf("Qual o id do carro que deseja adicionar?");
  scanf("%d", &i);

  struct Carro *c;
  printf("Digite a marca do carro: \n");
  scanf("%s", carros[i].marca);
  fprintf(arquivo, "%s\n", carros[i].marca);
  
  printf("\nQual o modelo do carro:\n");
  scanf("%s", carros[i].modelo);
  getchar();
  fprintf(arquivo, "%s\n", carros[i].modelo);

  printf("\nQual o ano de fabricacao do carro: \n");
  scanf("%d", &carros[i].ano_de_fabricacao);
  getchar();
  fprintf(arquivo, "%d\n", carros[i].ano_de_fabricacao);

  printf("\nQual a placa do carro: \n");
  scanf("%s", carros[i].Placa_do_Carro);
  getchar(); 
  fprintf(arquivo, "%s\n", carros[i].Placa_do_Carro);

  printf("\nQual a quilometragem do carro: \n");
  scanf("%d", &carros[i].Quilometragem);
  fprintf(arquivo, "%d\n", carros[i].Quilometragem);

  printf("\nQual o numero de portas do carro: \n");
  scanf("%d", &carros[i].numero_de_portas);
  fprintf(arquivo, "%d\n", carros[i].numero_de_portas);

  printf("O carro tem Ar condicionado(s/n): \n");
  scanf("%s", &carros[i].ar_condicionado);
  getchar();
  fprintf(arquivo, "%s\n", &carros[i].ar_condicionado);

  fclose(arquivo);
}

void opcao_dois(Carro* carros){
  int i=0, pos, qtd_carros, qtd_linhas=1, existe_linha=0;
  char leitor[1000], c;
  char placa[6], aux[15];

  FILE *arquivo;
  arquivo = fopen("carros.txt", "r");
  if (arquivo == NULL){
      printf("Não foi possível o arquivo");
  }
  FILE *arquivo2;
  arquivo2 = fopen("carros2.txt", "w");
  if (arquivo == NULL){
      printf("Não foi possível abrir o arquivo2");
  }

  printf("\n\nQual a placa do carro: \n");
  scanf("%s", placa);
  
  while(fscanf(arquivo, "%s", aux) != EOF){
    strcpy(carros[i].marca, aux);
    fscanf(arquivo, "%s", carros[i].modelo);
    fscanf(arquivo, "%d", &carros[i].ano_de_fabricacao);
    fscanf(arquivo, "%s", carros[i].Placa_do_Carro);
    fscanf(arquivo, "%d", &carros[i].Quilometragem);
    fscanf(arquivo, "%d", &carros[i].numero_de_portas);
    fscanf(arquivo, "%s", &carros[i].ar_condicionado);
    if (strcmp(carros[i].Placa_do_Carro, placa)==0){
      pos = i;
    }
    i++;
  }

  rewind(arquivo);
  c = getc(arquivo);

  while(c!=EOF){
    if(c=='\n'){
      qtd_linhas++;
    }
    c = getc(arquivo);
  }
  rewind(arquivo);
  qtd_carros = qtd_linhas/7;
  
  for (i=0; i<qtd_carros; i++){
    if (i==pos){
      printf("\nAlterando cadastro:");
      printf("\nDigite a nova marca:");
      scanf("%s", carros[pos].marca);
      fprintf(arquivo2, "%s\n", carros[pos].marca);
      printf("\nDigite o novo modelo:");
      scanf("%s", carros[pos].modelo);
      fprintf(arquivo2, "%s\n", carros[pos].modelo);
      printf("\nDigite o novo ano de fabricação:");
      scanf("%d", &carros[pos].ano_de_fabricacao);
      fprintf(arquivo2, "%d\n", carros[pos].ano_de_fabricacao);
      printf("\nDigite a nova placa do carro:");
      scanf("%s", carros[pos].Placa_do_Carro);
      fprintf(arquivo2, "%s\n", carros[i].Placa_do_Carro);
      printf("\nDigite a nova quilometragem:");
      scanf("%d", &carros[pos].Quilometragem);
      fprintf(arquivo2, "%d\n", carros[pos].Quilometragem);
      printf("\nDigite o novo numero de portas:");
      scanf("%d", &carros[pos].numero_de_portas);
      fprintf(arquivo2, "%d\n", carros[pos].numero_de_portas);
      printf("\nDigite o novo ar condicionado:");
      scanf("%s", &carros[pos].ar_condicionado);
      fprintf(arquivo2, "%s\n", &carros[pos].ar_condicionado);
    } else {
      fprintf(arquivo2, "%s\n", carros[i].marca);
      fprintf(arquivo2, "%s\n", carros[i].modelo);
      fprintf(arquivo2, "%d\n", carros[i].ano_de_fabricacao);
      fprintf(arquivo2, "%s\n", carros[i].Placa_do_Carro);
      fprintf(arquivo2, "%d\n", carros[i].Quilometragem);
      fprintf(arquivo2, "%d\n", carros[i].numero_de_portas);
      fprintf(arquivo2, "%s\n", &carros[i].ar_condicionado);
    }
  }

  rename("carros.txt", "old.txt");
  rename("carros2.txt", "carros.txt");
  remove("old.txt");
  fclose(arquivo);
  fclose(arquivo2);
}

void opcao_tres(Carro* carros){
  int i;
  char placa[6], aux[15];
  
  FILE *arquivo;
  arquivo = fopen("carros.txt", "r");
  if (arquivo == NULL){
      printf("Não foi possível o arquivo");
  }

  printf("\n\nQual a placa do carro: \n");
  scanf("%s", placa);

  while(fscanf(arquivo, "%s", aux) != EOF){
    strcpy(carros[i].marca, aux);
    fscanf(arquivo, "%s", carros[i].modelo);
    fscanf(arquivo, "%d", &carros[i].ano_de_fabricacao);
    fscanf(arquivo, "%s", carros[i].Placa_do_Carro);
    fscanf(arquivo, "%d", &carros[i].Quilometragem);
    fscanf(arquivo, "%d%*c", &carros[i].numero_de_portas);
    carros[i].ar_condicionado = fgetc(arquivo);
    fgetc(arquivo);

    if (strcmp(carros[i].Placa_do_Carro, placa)==0){
      printf("\nPlaca: %s\n", carros[i].Placa_do_Carro);
      printf("Marca: %s\n", carros[i].marca);
      printf("Modelo: %s\n", carros[i].modelo);
      printf("Ano de Fabricacao: %d\n", carros[i].ano_de_fabricacao);
      printf("Quilometragem: %d\n", carros[i].Quilometragem);
      printf("Numero de Portas: %d\n", carros[i].numero_de_portas);
      printf("Ar Condicionado: %c\n", carros[i].ar_condicionado);
    }
    i++;
  }
}

int main (){
  int n_cad;
  int i;

  Carro* carros = (Carro*)malloc(1000*sizeof(Carro));
  

  while (n_cad != 5){
    printf("\n1) Inserir novo cadastro de veiculo");
    printf("\n2) Alterar cadastro");
    printf("\n3) Mostrar os dados de um veiculo");
    printf("\n4) Apagar registro");
    printf("\n5) sair");

    printf("\nDigite uma opção de cadastro: ");
    scanf("%d", &n_cad);

    if (n_cad==1){
      opcao_um(carros);
    }
    if (n_cad==2){
      opcao_dois(carros);
    }
    if (n_cad==3){
      opcao_tres(carros);
    }
  }

  return 0;
}