#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int head = 0, tail = 0;

sem_t mutex, empty, full;

void *producer(void *arg) {
  int item;
  while (1) {
    // Generate item
    item = rand() % 100;

    // Acquire mutex
    sem_wait(&mutex);

    // Wait if buffer is full
    while ((tail + 1) % BUFFER_SIZE == head) {
      sem_post(&mutex);
      sem_wait(&empty);
      sem_wait(&mutex);
    }

    // Add item to buffer
    buffer[tail] = item;
    tail = (tail + 1) % BUFFER_SIZE;

    // Signal full and release mutex
    sem_post(&full);
    sem_post(&mutex);

    printf("Produced: %d\n", item);
  }
}

void *consumer(void *arg) {
  int item;
  while (1) {
    // Acquire mutex
    sem_wait(&mutex);

    // Wait if buffer is empty
    while (head == tail) {
      sem_post(&mutex);
      sem_wait(&full);
      sem_wait(&mutex);
    }

    // Remove item from buffer
    item = buffer[head];
    head = (head + 1) % BUFFER_SIZE;

    // Signal empty and release mutex
    sem_post(&empty);
    sem_post(&mutex);

    printf("Consumed: %d\n", item);
  }
}

int main() {
  pthread_t producer_thread, consumer_thread;

  // Initialize semaphores
  sem_init(&mutex, 0, 1);
  sem_init(&empty, 0, BUFFER_SIZE);
  sem_init(&full, 0, 0);

  // Create producer and consumer threads
  pthread_create(&producer_thread, NULL, producer, NULL);
  pthread_create(&consumer_thread, NULL, consumer, NULL);

  // Join threads (for demonstration)
  pthread_join(producer_thread, NULL);
  pthread_join(consumer_thread, NULL);

  // Destroy semaphores
  sem_destroy(&mutex);
  sem_destroy(&empty);
  sem_destroy(&full);

  return 0;
}
