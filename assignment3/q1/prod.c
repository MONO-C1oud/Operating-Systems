#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/shm.h>
#include <semaphore.h>

sem_t mutex;
int counter; //shared variable


void producer() {
	system("./cons");
}

int main() {
	pthread_t prodthread; 
	int* sharedmem;
	int shmid;
	int size = 100;
	shmid = shmget((key_t)1080, size, 0666|IPC_CREAT);
	sharedmem = shmat(shmid,NULL,0);

	pthread_create(&prodthread, NULL, producer, NULL);

	sem_init(&mutex, 1, 1);
	printf("\nproducing...\n");
	for (int i = 0; i < size; i++) {
		sem_wait(&mutex);
		sharedmem[i] = rand() % 100;
		printf("%d\n", sharedmem[i]);
		sem_post(&mutex);
	}
	
	sem_destroy(&mutex);
	pthread_join(prodthread, NULL);
	return 0;
}