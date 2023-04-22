#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_rwlock_t rwlock; // Reader-writer lock

void *reader(void *arg) {
    int *data = (int *)arg;

    // Acquire read lock
    pthread_rwlock_rdlock(&rwlock);

    // Read data from the resource
    printf("Reader %lu: data = %d\n", pthread_self(), *data);

    // Release read lock
    pthread_rwlock_unlock(&rwlock);

    return NULL;
}

void *writer(void *arg) {
    int *data = (int *)arg;

    // Acquire write lock
    pthread_rwlock_wrlock(&rwlock);

    // Update the resource
    *data = *data + 1;
    printf("Writer: data = %d\n", *data);

    // Release write lock
    pthread_rwlock_unlock(&rwlock);

    return NULL;
}

int main() {
    pthread_t reader_threads[2], writer_thread;
    int data = 0;

    // Initialize the reader-writer lock
    pthread_rwlock_init(&rwlock, NULL);

    // Create the reader threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&reader_threads[i], NULL, reader, &data);
    }

    // Create the writer thread
    pthread_create(&writer_thread, NULL, writer, &data);

    // Wait for the threads to finish
    for (int i = 0; i < 2; i++) {
        pthread_join(reader_threads[i], NULL);
    }
    pthread_join(writer_thread, NULL);

    // ----------------------------
    // Reading again
    
    // Create the reader threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&reader_threads[i], NULL, reader, &data);
    }

    // Create the writer thread
    pthread_create(&writer_thread, NULL, writer, &data);

    // Wait for the threads to finish
    for (int i = 0; i < 2; i++) {
        pthread_join(reader_threads[i], NULL);
    }
    pthread_join(writer_thread, NULL);

    // ----------------------------

    // Destroy the reader-writer lock
    pthread_rwlock_destroy(&rwlock);

    return 0;
}
