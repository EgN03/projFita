/* Projeto 1 - Fita Cassete
Integrantes:
	Enrique Granado Novaes 32107803
	Enzo Rocha Damato 32125992 */
#include <stdio.h>
#include <stdlib.h> //Biblioteca para chamar o malloc()
#include <stdbool.h>
int at=0;

//Função para imprimir as combinações da fita do lado A e B.
void imprima(int perm[],int n,int tam){ //C:\Users\Rosangela\Desktop\ProjAnlise1\projFita\musicas.txt
    int i;
    int min, seg,min1,seg1, a;
    printf("Lado A\n");//Imprime o lado A
    for(i = 0; i < n; i++)
        printf("%d min %d seg\n",perm[i]/60,perm[i]%60); //Converte de segundos para minutos na resolução final.
        //printf("%d  \n",perm[i]);

    printf("Lado B\n");//Imprime o lado B
    for(i = n; i < tam; i++)
        //printf("%d  \n",perm[i]);
        printf("%d min %d seg\n",perm[i]/60,perm[i]%60);//Converte de segundos para minutos na resolução final.
}
bool valida(int s[],int i){
	int j;
    for(j=0; j < i; j++)
        if(s[i]==s[j])
            return false;

    return true;

}
//Função Verificação confere se a permutação atual cabe dentro da fita
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
//Função Permutação gera todas as permutações possiveis para as musicas
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

//Função para gravar as músicas na fita lado A e B.
void grava(int musicas[], int tempo,int nMusicas){
	int* perm = malloc(nMusicas * sizeof(int)); //Aloca a um espaço x de memória
	if(permuta(musicas,nMusicas,perm,0,tempo) == false)printf("nao ha como gravar as musicas continuamente\n");
}

//Função para ler o arquivo txt.
//Para fica mais fácil de fazer o código, fizemos a conversão de minutos para segundos.
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
		if(total > tamanho*60){ //Combinação das músicas ultrapassa o tempo disponível para cada lado.
			printf("essas musicas nao cabem na fita\n");
		}
		else{
			grava(musicas, tamanho, nMusicas); //Chama a função Grava().
		}
	}
}

int main()
{
	FILE *arquivo;
	char nome[100]; //= "D:/mack/projAlg2/projFita-master/projFita-master/musicas.txt";
	printf("Qual o caminho do arquivo?\n"); //Digite o caminho que o txt está.
	scanf("%s",nome);
	printf("%s\n",nome);
	arquivo = fopen(nome,"r"); //Lê o arquivo txt.
	while(arquivo == NULL){
		printf("arquivo nao encontrado, digite o caminho completo e a extensao:\n");
		scanf("%s",nome);
		arquivo = fopen(nome,"r");
	}
	lerAquivo(arquivo);//Leitura do arquivo

    return 0;
}
