#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int vagas = 200;

void *painel (void *myvar){
	char *msg;
	msg = (char *) myvar;

	int i;
	for(i=0; i<10; i++){
		printf("%s %d\n", msg, vagas);
		sleep(1);
	}
	return 0;
}

int main(){
	pthread_t thread1;
	char *msg1 = "Numero de vagas disponiveis:";
	int ret1;

	ret1 = pthread_create(&thread1, NULL, painel, (void *) msg1);

	printf("Main function after pthread_create\n");

	pthread_join(thread1, NULL);

	printf("First thread ret1 = %d\n", ret1);
	
	return 0;
}

