#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int vagas = 200;

void *painel (void *arg){
	int *painel_num = (int *) arg;
	int painel = *painel_num;

	printf("Painel %d\nNumero de vagas disponiveis: %d\n\n",painel ,vagas);

	pthread_exit(0);
}

int main(){
	int num_painel = 5;
	pthread_t tid[num_painel]; 
	int i;
	for(i=0; i<num_painel; i++){
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tid[i], &attr, painel, &i);
	}

	printf("Main function after pthread_create\n");
	
	for(i=0; i<num_painel; i++){
		pthread_join(tid[i], NULL);
	}	

	return 0;
}

