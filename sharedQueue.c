#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>

#define QUEUE_SIZE 100
#define NUM_READERS 5
#define NUM_MESSAGES 25

struct Queue {
    char* messages[QUEUE_SIZE];
    int front, rear;
    sem_t empty_slots, used_slots;
    pthread_mutex_t mutex;
};

struct Queue queue;

void initQueue() {
    queue.front = queue.rear = 0;
    sem_init(&queue.empty_slots, 0, QUEUE_SIZE);
    sem_init(&queue.used_slots, 0, 0);
    pthread_mutex_init(&queue.mutex, NULL);
}

void enqueue(const char* message) {
    sem_wait(&queue.empty_slots);
    pthread_mutex_lock(&queue.mutex);

    queue.messages[queue.rear] = strdup(message);
    queue.rear = (queue.rear + 1) % QUEUE_SIZE;

    pthread_mutex_unlock(&queue.mutex);
    sem_post(&queue.used_slots);
}

char* dequeue() {
    sem_wait(&queue.used_slots);
    pthread_mutex_lock(&queue.mutex);

    char* message = queue.messages[queue.front];
    queue.front = (queue.front + 1) % QUEUE_SIZE;

    pthread_mutex_unlock(&queue.mutex);
    sem_post(&queue.empty_slots);

    return message;
}

void* writer(void* arg) {
    for (int i = 0; i < NUM_MESSAGES; i++) {
        char message[20];
        snprintf(message, sizeof(message), "Message %d", i);
        enqueue(message);
        usleep(200000);  // Sleep for 200ms (5 messages per second)
    }
    pthread_exit(NULL);
}

void* reader(void* arg) {
    while (1) {
        char* message = dequeue();
        printf("Reader %d received: %s\n", *((int*)arg), message);
        free(message);
    }
}

int main() {
    initQueue();

    pthread_t writerThread;
    pthread_create(&writerThread, NULL, writer, NULL);

    pthread_t readerThreads[NUM_READERS];
    int readerIds[NUM_READERS];

    for (int i = 0; i < NUM_READERS; i++) {
        readerIds[i] = i + 1;
        pthread_create(&readerThreads[i], NULL, reader, &readerIds[i]);
    }

    pthread_join(writerThread, NULL);
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_cancel(readerThreads[i]);
    }

    sem_destroy(&queue.empty_slots);
    sem_destroy(&queue.used_slots);
    pthread_mutex_destroy(&queue.mutex);

    return 0;
}

