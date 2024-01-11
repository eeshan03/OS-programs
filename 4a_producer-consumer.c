#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 10

int buffer[BUFFER_SIZE];
sem_t mutex, empty_slots, filled_slots;

void *producer(void *arg) {
    int item;
    for (int i = 0; i < MAX_ITEMS; i++) {
       
        item = rand() % 100 + 1;
        sem_wait(&empty_slots);
        sem_wait(&mutex);

        for (int j = 0; j < BUFFER_SIZE; j++) {
            if (buffer[j] == 0) {
                buffer[j] = item;
                break;
            }
        }

        printf("Produced %d, Buffer:", item);
        for (int j = 0; j < BUFFER_SIZE; j++) {
            if (buffer[j] != 0) {
                printf(" %d", buffer[j]);
            }
        }
        printf("\n");

        sem_post(&mutex);
        sem_post(&filled_slots);
       
        usleep(rand() % 500000 + 100000); // Sleep for a random time
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;
    for (int i = 0; i < MAX_ITEMS; i++) {
       
        sem_wait(&filled_slots);
        sem_wait(&mutex);

        for (int j = 0; j < BUFFER_SIZE; j++) {
            if (buffer[j] != 0) {
                item = buffer[j];
                buffer[j] = 0;
                break;
            }
        }

        printf("Consumed %d, Buffer:", item);
        for (int j = 0; j < BUFFER_SIZE; j++) {
            if (buffer[j] != 0) {
                printf(" %d", buffer[j]);
            }
        }
        printf("\n");

        sem_post(&mutex);
        sem_post(&empty_slots);
       
        usleep(rand() % 500000 + 100000); // Sleep for a random time
    }
    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    sem_init(&mutex, 0, 1);
    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&filled_slots, 0, 0);
    

    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&mutex);
    sem_destroy(&empty_slots);
    sem_destroy(&filled_slots);
   

    printf("All threads have finished.\n");

    return 0;
}
