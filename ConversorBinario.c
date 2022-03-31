#include <stdio.h>
#include <stdlib.h>

// Struct das Pilhas
typedef struct {
  // topo (int) - indexador (guarda o indice de posicoes do vetor)
  int topo;
  int vetor[10];
} PilhaEstatica;

//----------------------//
//      Operações       //
//----------------------//

// Inicialização da Pilha 
void inicializarPilhaEstatica(PilhaEstatica *p) {
  p->topo = 0;
}

// Adiciona valor na Pilha
void empilharPilhaEstatica(PilhaEstatica *pilha, int x) {
    // Add o numero (x) na posicao indexada pelo topo
    pilha->vetor[pilha->topo] = x;
    // Incrementa o valor do topo
    pilha->topo++;
}

// Remove valor do topo da Pilha
int desempilharPilhaEstatica(PilhaEstatica *pilha) {
    // Topo decrementado retornar uma posicao
    int temporario = pilha->vetor[pilha->topo-1];
	pilha->topo--;
	return temporario;
}

// Retorna o valor da pilha
int topoPilhaEstatica(PilhaEstatica *pilha) {
  int ret = pilha->vetor[pilha->topo-1];
  return(ret);
}

// Imprime o que tem na pilha
void imprimirPilhaEstatica(PilhaEstatica *p, char nome[8]) {
  printf("\nPilha %s = [", nome);
  int i;
  for(i = 0; i < p->topo; i++) {
    printf("%d ", p->vetor[i]);
  }
  printf("]\n");
}

// Converte um número do arquivo de entrada para binários
int converteParaBinario(PilhaEstatica *pBin, int decimal){
	int decimalGuarda = decimal;
	int resultado[10], i;
	int binario = 0;
	if(decimal == 1){
		empilharPilhaEstatica(pBin, 1);
	}
	else if(decimal == 0){
		empilharPilhaEstatica(pBin, 0);
	}else{
		for(i=0; decimal>0; i++){
			resultado[i] = decimal%2;
			decimal/=2;
		}
		for(i=i-1; i>=0; i--){
			binario*=10;
			binario += resultado[i];
		}
		empilharPilhaEstatica(pBin, binario);	
	}
}

int main(int argc, const char * argv[]) {
  // Usando o argc 
  printf("Numero de parametros fornecidos: %d\n", argc);
  
  //Verifica os parâmetros
  if(argc!= 3) {
    printf("Quantidade de parametros invalida\n");
    return 0;
  }  

  FILE* entrada = fopen(argv[1], "r");
  FILE* saida   = fopen(argv[2], "w");

  // Checa erros de abertura de arquivo
  if(entrada == NULL || saida == NULL) {
     printf("Erro: algum dos arquivos não pode ser criado corretamente\n");
     return 0;
  }
  
  // Inicializa a pilha de Entrada
  PilhaEstatica pilhaEntrada;
  inicializarPilhaEstatica(&pilhaEntrada);  	  
  
  // Verifica se o arquivo está vazio
  char teste;
  if((teste = fgetc(entrada)) == EOF){
  	printf("Erro: Arquivo inválido\n");
 	fprintf(saida, "Erro: Arquivo inválido");
	return 0;
  }
  
  // Retorna para o início do arquivo
  rewind(entrada);
  
  // Verifica se os caracteres do arquivo de entrada são válidos
  while((teste = fgetc(entrada)) != EOF) {
  	if(!(teste=='0' ||teste=='1' ||teste=='2' ||teste=='3' ||teste=='4' ||teste=='5' ||teste=='6' ||teste=='7' ||teste=='8' ||teste=='9' || teste=='\n')){
  		printf("Erro: Arquivo inválido\n");
     	fprintf(saida, "Erro: Arquivo inválido");
		return 0;
	}
  }
  rewind(entrada);

  int decimal;
  while(!feof(entrada)) {
    // Obtendo inteiro do arquivo de entrada
    fscanf(entrada, "%d", &decimal);
    // Escreve esse inteiro no arquivo de saida
  	empilharPilhaEstatica(&pilhaEntrada, decimal);
  }
  char imprimeNome1[8] = "Entrada";
  imprimirPilhaEstatica(&pilhaEntrada, imprimeNome1);
  
  //Inicializa a pilha de Binário
  PilhaEstatica pilhaBinario;
  inicializarPilhaEstatica(&pilhaBinario);
  
  //Usado para saber o tamanho da pilha
  int temp = pilhaEntrada.topo;
  int i;
  for(i=0; i<temp; i++){
  	// Converte para binário
	converteParaBinario(&pilhaBinario, desempilharPilhaEstatica(&pilhaEntrada));
  	// Escreve o número convertido no arquivo
	fprintf(saida, "%d\n", pilhaBinario.vetor[pilhaBinario.topo-1]);
  }
  char imprimeNome2[8] = "Saida";
  imprimirPilhaEstatica(&pilhaBinario, imprimeNome2);
  
  // Fecha os dois arquivos
  fclose(entrada);
  fclose(saida);
  return 0;
}
