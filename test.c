#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int vagas = 200, carros = 0;

void *painel (void *arg){
	int *painel_num = (int *) arg;
	int painel = *painel_num;

	printf("Painel %d\nNumero de vagas disponiveis: %d\n\n", painel, vagas);

	pthread_exit(0);
}
/*
void *carro (void *arg){
	carros++;
	vagas--;	
	int i;
	for(i=0; i<50; i++){	
	printf("Carro %d dentro do estacionamento\n", carros);
	
	
	
	vagas++;
	carros++;
	printf("Carro %d fora do estacionamento\n", carros);
	}

	pthread_exit(0);
}*/

int main(){
	int num_painel = 3, exit = 1;
	pthread_t tid[num_painel], thread_carro; 
	int i, x, counter = 50;
	
	while(exit != 0){
		printf("Aperte 0 para parar de executar o programa.");
		scanf("%d\n", &exit);
		for(i=0; i<num_painel; i++){
			pthread_attr_t attr;
			pthread_attr_init(&attr);
			x=i+1;
			pthread_create(&tid[i], &attr, painel, &x);
		}
		/*
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&thread_carro, &attr, carro, &counter);			
		
		pthread_join(thread_carro, NULL);*/		
		
		for(i=0; i<num_painel; i++){
			pthread_join(tid[i], NULL);
		}
	}	

	return 0;
}

