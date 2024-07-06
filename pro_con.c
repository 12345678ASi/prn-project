#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 5

typedef struct {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} Monitor;

void init_monitor(Monitor *monitor) {
    monitor->in = 0;
    monitor->out = 0;
    monitor->count = 0;
    pthread_mutex_init(&monitor->mutex, NULL);
    pthread_cond_init(&monitor->not_empty, NULL);
    pthread_cond_init(&monitor->not_full, NULL);
}

void insert_item(Monitor *monitor, int item) {
    pthread_mutex_lock(&monitor->mutex);

    while (monitor->count == BUFFER_SIZE) {
        pthread_cond_wait(&monitor->not_full, &monitor->mutex);
    }

    monitor->buffer[monitor->in] = item;
    monitor->in = (monitor->in + 1) % BUFFER_SIZE;
    monitor->count++;

    pthread_cond_signal(&monitor->not_empty);
    pthread_mutex_unlock(&monitor->mutex);
}

int remove_item(Monitor *monitor) {
    int item;

    pthread_mutex_lock(&monitor->mutex);

    while (monitor->count == 0) {
        pthread_cond_wait(&monitor->not_empty, &monitor->mutex);
    }

    item = monitor->buffer[monitor->out];
    monitor->out = (monitor->out + 1) % BUFFER_SIZE;
    monitor->count--;

    pthread_cond_signal(&monitor->not_full);
    pthread_mutex_unlock(&monitor->mutex);

    return item;
}

void *producer(void *arg) {
    Monitor *monitor = (Monitor *)arg;
    for (int i = 0; i < 10; i++) {
        insert_item(monitor, i);
        printf("Produced item: %d\n", i);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    Monitor *monitor = (Monitor *)arg;
    int item;
    for (int i = 0; i < 10; i++) {
        item = remove_item(monitor);
        printf("Consumed item: %d\n", item);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;
    Monitor monitor;

    init_monitor(&monitor);

    pthread_create(&producer_thread, NULL, producer, (void *)&monitor);
    pthread_create(&consumer_thread, NULL, consumer, (void *)&monitor);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    pthread_mutex_destroy(&monitor.mutex);
    pthread_cond_destroy(&monitor.not_empty);
    pthread_cond_destroy(&monitor.not_full);

    return 0;
}
