#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *print_thread(void *arg) {

    pthread_mutex_lock(&mutex);
    // critical section
    printf("Printing...\n");
    sleep(2); // simulate printing time
    // critical section end
    pthread_mutex_unlock(&mutex);
    return NULL;

}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, print_thread, NULL);
    pthread_create(&thread2, NULL, print_thread, NULL);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}