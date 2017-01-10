#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

typedef sem_t Semaphore;

Semaphore vagas;
Semaphore mutex;

void *painel1 (void *arg){
	int *painel_num = (int *) arg;
	int painel = *painel_num;

	printf("Painel 1\nNumero de vagas disponiveis: %d\n\n", painel);

	pthread_exit(0);
}

void *painel2 (void *arg){
	int *painel_num = (int *) arg;
	int painel = *painel_num;

	printf("Painel 2\nNumero de vagas disponiveis: %d\n\n", painel);

	pthread_exit(0);
}

void *carro (void *arg){
	int *painel_num = (int *) arg;
	int painel = *painel_num;
	int loop = 1;
	while(loop){	
		sem_wait(&mutex);
		sem_wait(&vagas);

		printf("Carro %d dentro do estacionamento\n", painel);
		
		sem_post(&mutex);
	
		sleep(10);

		printf("Carro %d fora do estacionamento\n", painel);
		
		sem_post(&vagas);
	}
}

int main(){
	pthread_t thread_painel1, thread_painel2, thread_carro; 
	int i, x, counter = 50;

	sem_init(&vagas, 0, 50);
	sem_init(&mutex, 0, 1);
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&thread_painel1, &attr, painel1, &counter);
	pthread_create(&thread_painel2, &attr, painel2, &counter);	
	
	/*for(i=0; i<num_painel; i++){
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		x=i+1;
		pthread_create(&tid[i], &attr, painel, &x);
	}
		
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&thread_carro, &attr, carro, &counter);			
		
		pthread_join(thread_carro, NULL);		
		
		for(i=0; i<num_painel; i++){
			pthread_join(tid[i], NULL);
		}
	}	*/

	pthread_join(thread_painel1, NULL);
	pthread_join(thread_painel2, NULL);

	sem_destroy(&vagas);
	sem_destroy(&mutex);

	return 0;
}
