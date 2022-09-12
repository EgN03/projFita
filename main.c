#include <stdio.h>
#include <stdlib.h>

void lerAquivo(FILE* arquivo){
	int nTestes, tamanho, nMusicas, minutos, segundos,i,j;
	fscanf(arquivo, "%d", &nTestes);
	for(i=0;i<nTestes;i++){
		fscanf(arquivo, "%d", &tamanho);
		printf("tamanho %d\n", tamanho);
		
		fscanf(arquivo, "%d", &nMusicas);
		printf("num %d\n", nMusicas);
		for(j=0;j<nMusicas;j++){
			fscanf(arquivo, "%d", &minutos);
			printf("minutos %d\n", minutos);
			
			fscanf(arquivo, "%d", &segundos);
			printf("segundos %d\n", segundos);
		}
	}
}

int main()
{
	FILE *arquivo;
	char nome[100];
	printf("Qual o caminho do arquivo?\n");
	scanf("%s",nome);
	//printf("%s\n",nome);
	arquivo = fopen(nome,"r");
	while(arquivo == NULL){
		printf("arquivo nao encontrado, digite o caminho completo e a extensao:\n");
		scanf("%s",nome);
		arquivo = fopen(nome,"r");
	}
	lerAquivo(arquivo);
	
    return 0;
}
