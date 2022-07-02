#include<stdio.h>
#include<stdlib.h>

typedef struct p{
	int I;  // 10<=Idade<=90
	int T;  // 0<=Tempo<=840  de chegada
	int D;  // 2<=Demora<=10  no atendimento
	struct p *prox;
}Pes;

typedef struct c{
	Pes* cliente;
	struct c *prox;
}cx;

void print_lista(Pes*);

void add_pes(Pes**, Pes*, Pes**); // entra na fila

void insertion_sort(Pes*, int);	// ordenar vetor de entradas (<T, if T === then >I)

int caixa_livre(int, cx**);  // fun?ao para verificar se os caixas estao ocupados e libera-los

void set_caixa(cx**, cx*, cx**);  // cria?ao do buffer de caixas

int main(void){
	Pes *primeiro=NULL, *vetPes, *aux, *ultimo;
	cx *vetCx, *caixa=NULL, *auxcx;
	int N, M, i=0, tpas=0, tAnt=0, tAgr=0, pegaFila=0, flag=1;// 1<=N<=10^3 // M (num caixas)
	
	scanf("%d ", &N);
	scanf("%d", &M);
	
	vetPes=malloc(N*sizeof(Pes));
	vetCx=malloc(M*sizeof(cx));
	
	for(i=0;i<M;i++){ // prepara?ao dos caixas
		(vetCx+i)->prox=malloc(sizeof(cx));
		(vetCx+i)->prox=vetCx+i;
		(vetCx+i)->cliente=NULL;
		set_caixa(&caixa,vetCx+i, &auxcx);		
	}
	i=0;
	
	for(i=0;i<N;i++){  // atrada dos dados e prepara?ao da fila
		scanf("%d", &(vetPes+i)->I);
		scanf("%d", &(vetPes+i)->T);
		scanf("%d", &(vetPes+i)->D);
		(vetPes+i)->prox=malloc(sizeof(Pes));
		(vetPes+i)->prox=NULL;}
	i=0;
	
	insertion_sort(vetPes, N); // ordena?ao por tempo e idade
	
	//for(i=0;i<N;i++) printf("\n\n\t%d %d %d \n", (vetPes+i)->I, (vetPes+i)->T, (vetPes+i)->D); i=0; // print das informa?oes
	
	for(i=0;i<N;i++){
		aux=(vetPes+i);
		auxcx=caixa;
		flag=1;  //informa o cliente atual foi ou nao atendido
		tAnt=tAgr;  //tempo antes
		tAgr=(aux->T);  //tempo agora
		tpas=tAgr-tAnt; //tempo passado entre chegada de um cliente e outro
		
	
		 
		if(caixa_livre(tpas, &caixa)){ // algum caixa livre
		
			do{
				
				if((!(caixa->cliente)) && !primeiro){  // caixa livre e sem fila
					caixa->cliente=aux;
					flag=0;
				}
				
				if(!(caixa->cliente) && primeiro){ // caixa livre e cliente na fila
					caixa->cliente=primeiro;
					primeiro=primeiro->prox;
				}
				
				caixa=caixa->prox;
			}while(caixa!=auxcx && flag);
			if(flag)
				add_pes(&primeiro, aux, &ultimo);
		}
		else 
			add_pes(&primeiro, aux, &ultimo);
		
		
		
		if(tAgr!=(vetPes+(i+1))->T){
			print_lista(primeiro);
		}
		
	}

	return 0;
	
}






void print_lista(Pes* lista){
	Pes* aux;
	aux=lista;
	printf("\n\n");
	
	if(!(lista)){
	printf("\tNULL");
	return;}
	
	do{
		printf("\t%d", aux->I);
		aux=aux->prox;
		
	
	}while(aux);
	
	return;
}






void add_pes(Pes** primeiro, Pes* pess, Pes** ultimo){ // adiciona a fila com preferencia para idosos
	Pes* aux=*primeiro;
	
	if (!(*primeiro)){
		*(primeiro)=pess; 
		*(ultimo)=pess;
		return;}
	
	if(pess->I >= 64){
		while(aux->I > pess->I){
			if(!(aux->prox)) break;
			aux=aux->prox;
		}
		if(aux==*primeiro && aux->I<pess->I){
			pess->prox=*primeiro;
			*primeiro=pess;
			return;
		}
		else{
			pess->prox=aux->prox;
			aux->prox=pess;
			if(aux==*ultimo) *ultimo=pess;
			return;
		}
	}
	
	else{
		aux=*(ultimo);
		aux->prox=pess;
		*(ultimo)=pess;
		pess=NULL;
	}
	
	return;
	
}


int caixa_livre(int temp_pas, cx** caixa){  // retorna 1 se tem algum caixa livre
	int flag=0;
	cx* aux=*caixa;
	
	do{
		
		if(aux->cliente){
			(aux->cliente)->D-=temp_pas;
			if(((aux->cliente)->D)<=0){
				aux->cliente=NULL;
				flag=1;
			}
		}	
		
		
		
		else 
			flag=1;
		
		aux=aux->prox;
		
	}while(aux != *caixa);
	
	
	return flag;
}






void insertion_sort(Pes* vet, int n){   // organiza o vetor por tempo de chegada (ou idade qnd chegam ao mesmo tempo)
	int i, j, valor;
	Pes aux;
	
	for(i=1; i<n; i++){ // por tempo de chegada
		aux= vet[i];
		valor=vet[i].T;
		j=i;
		while(j>0 && vet[j-1].T > valor){
				
			vet[j]=vet[j-1];
			j--;
		}
		vet[j]=aux;
		
		if(valor==vet[j-1].T){
			while(j>0 && valor==vet[j-1].T && vet[i].I>vet[j-1].I){
				
				vet[j]=vet[j-1];
				j--;
			}
			vet[j]=aux;
		}
	}

}


void set_caixa(cx** inicio, cx* novo, cx** cauda){  // adiciona caixa ao buffer
	//cx* aux=*inicio;
	
	if(!(*inicio)){
		*inicio=novo;
		*cauda=novo;
		return;
	}
	novo->prox=(*cauda)->prox;
	(*cauda)->prox=novo;

	return;
}














