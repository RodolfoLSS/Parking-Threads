#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/types.h>
#include<sys/syscall.h>

sem_t vagas;
sem_t mutex;
int carro_num = 0;

void *painel1 (void *arg){
	int *painel_num = (int *) arg;
	int painel = *painel_num;
	int loop = 1;

	while(loop){
		printf("Painel 1\nNumero de vagas disponiveis: %d\n\n", 50-carro_num);
		sleep(3);
	}

	pthread_exit(0);
}

void *painel2 (void *arg){
	int *painel_num = (int *) arg;
	int painel = *painel_num;
	int loop = 1;

	while(loop){
		printf("Painel 2\nNumero de vagas disponiveis: %d\n\n", 50-carro_num);
		sleep(2);
	}

	pthread_exit(0);
}

void *carro (void *arg){
	int loop = 1;
	pid_t id = syscall(__NR_gettid);
	
	while(loop){	
		sem_wait(&mutex);
		sem_wait(&vagas);

		carro_num++;
		printf("Carro %d dentro do estacionamento\n", id-21600);
		sem_post(&mutex);
	
		sleep(5);

		printf("Carro %d fora do estacionamento\n", id-21600);
		carro_num--;
		
		sem_post(&vagas);

		sleep(10);
	}
}

int main(){
	pthread_t thread_painel1, thread_painel2, thread_carro[100]; 
	int i, x, carros = 100;

	sem_init(&vagas, 0, 50);
	sem_init(&mutex, 0, 1);
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&thread_painel1, &attr, painel1, &carros);
	pthread_create(&thread_painel2, &attr, painel2, &carros);	

	for(i=0; i<carros; i++){
		pthread_create(&thread_carro[i], &attr, carro, &i);
	}		
		
	for(i=0; i<carros; i++){
		pthread_join(thread_carro[i], NULL);
	}

	pthread_join(thread_painel1, NULL);
	pthread_join(thread_painel2, NULL);

	sem_destroy(&vagas);
	sem_destroy(&mutex);

	return 0;
}
