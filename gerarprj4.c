#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int gerar(int);

int seed;

int main(){
	int N, I, T, D, op, M;
	srand(time(NULL));	
	FILE *fp;
	fp=fopen("teste.txt", "w");
	
	seed=0;
	
	N=gerar(0);
	fprintf(fp, "%d ", N);
	
	M=gerar(4);;
	fprintf(fp, "%d\n", M);
	
	while(N){
		I=gerar(1);
		T=gerar(2);
		D=gerar(3);
		fprintf(fp, "%d %d %d\n", I, T, D);
		N--;
	}
	fclose(fp);
}


int gerar(int op){

	seed++;	
	int randao;
	
	if(op==0) {  //N
		do{
			randao = (rand() % 30);
		}while (randao<6 || randao>30);
		return randao;
	}
	
	if(op==1){  //I
		do{
			randao = (rand() % 90); 
		//	randao*=seed;
		}while (randao<10 || randao>90);
		
		return randao;
	}
	
	if(op==2){  //T
		do{
			randao = (rand() % 14); 
		//	randao*=seed;
		}while (randao<2 || randao>840);
		
		return randao;
	}
	
	if(op==3){  //D
		do{
			randao = (rand() % 9);  
		//	randao*=seed;
		}while (randao<2 || randao>10);
		
		return randao;
	}
	
		if(op==4){  //D
		do{
			randao = (rand() % 4);  
		//	randao*=seed;
		}while (randao<2 || randao>4);
		
		return randao;
	}
	
}

