#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int at=0;

void imprima(int perm[],int n,int tam){
    int i;
    printf("Lado A\n");
    for(i = 0; i < n; i++)
        printf("%d  \n",perm[i]);
    printf("Lado B\n");
    for(i = n; i < tam; i++)
        printf("%d  \n",perm[i]);
}
bool valida(int s[],int i){
	int j;
    for(j=0; j < i; j++)
        if(s[i]==s[j])
            return false;

    return true;

}
int verifica(int perm[], int nMusicas,int tempo){
	int a=0,b=0,*fita = malloc(nMusicas * sizeof(int)),soma=0;
	while(soma<tempo*30){
		if(soma+perm[a]<=tempo*30){
			fita[a] = perm[a];
			soma += fita[a++];
		}
		else{
			break;
		}
	}
	soma=0;
	for(b=a;b<nMusicas;b++){
		fita[b] = perm[b];
		soma += fita[b];
		
	}
	if(soma>tempo*60/2)
		return -1;
	
	return a;
}
bool permuta(int musicas[], int nMusicas, int perm[],int i,int tempo){
    if( i >= nMusicas){ // caso base
    	int a;
 		if((a = verifica(perm,nMusicas,tempo)) > 0){
 			imprima(perm,a,nMusicas);
         	return true;
        }
 	}
	else{
    	int j;
		bool a;
        for(j=0; j <nMusicas; j++){
        	perm[i] = musicas[j];
            if(valida(perm,i))
                a = permuta(musicas,nMusicas,perm,i+1,tempo);
                if(a==true)return a;
        }
    }
    return false;
}

void grava(int musicas[], int tempo,int nMusicas){
	int* perm = malloc(nMusicas * sizeof(int));
	if(permuta(musicas,nMusicas,perm,0,tempo) == false)printf("nao ha como gravar as musicas continuamente\n");
}

void lerAquivo(FILE* arquivo){
	int nTestes, tamanho, nMusicas, minutos, segundos,i,j,total,tMusica;
	fscanf(arquivo, "%d", &nTestes);
	for(i=0;i<nTestes;i++){
		total =0;
		fscanf(arquivo, "%d", &tamanho);
		printf("\ntamanho %d\n", tamanho);
		
		fscanf(arquivo, "%d", &nMusicas);
		//printf("num %d\n", nMusicas);
		
		int* musicas =(int*)malloc(nMusicas * sizeof(int));
		for(j=0;j<nMusicas;j++){
			fscanf(arquivo, "%d", &minutos);
			//printf("minutos %d\n", minutos);
			
			fscanf(arquivo, "%d", &segundos);
			//printf("segundos %d\n", segundos);
			tMusica = segundos+minutos*60;
			total += tMusica;
			musicas[j]=tMusica;
		}
		if(total > tamanho*60){
			printf("essas musicas nao cabem na fita\n");
		}
		else{
			grava(musicas, tamanho, nMusicas);
		}
	}
}

int main()
{
	FILE *arquivo;
	char nome[100]; //= "D:/mack/projAlg2/projFita-master/projFita-master/musicas.txt";
	printf("Qual o caminho do arquivo?\n");
	scanf("%s",nome);
	printf("%s\n",nome);
	arquivo = fopen(nome,"r");
	while(arquivo == NULL){
		printf("arquivo nao encontrado, digite o caminho completo e a extensao:\n");
		scanf("%s",nome);
		arquivo = fopen(nome,"r");
	}
	lerAquivo(arquivo);
	
    return 0;
}
