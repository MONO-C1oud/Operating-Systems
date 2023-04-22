#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex;
int counter; //shared variable


int main() {
	int* sharedmem;
	int shmid;
	int size = 4;
	shmid = shmget((key_t)1080, size, 0666|IPC_CREAT);
	sharedmem = shmat(shmid,NULL,0);

	sem_init(&mutex, 1, 1);
	printf("\nthis is p2...\n");
	for (int i = 0; i < size/4; i++) {
		sem_wait(&mutex);
		printf("accessing memory...(memory used by p2)\n");
		sem_post(&mutex);
	}
	
	sem_destroy(&mutex);
	return 0;
}
