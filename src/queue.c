#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

void queue_init ( task_queue_t *q, size_t capacity){
    q-> head = NULL;
    q-> tail = NULL;
    q-> size = 0; 
    q-> capacity = capacity;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->notEmpty, NULL);
    pthread_cond_init(&q->notFull, NULL);
}

void queue_push (task_queue_t *q, task_t *task) {
    pthread_mutex_lock(&q->lock); // Lock the queue for thread safety
    while (q->size == q->capacity) {
        pthread_cond_wait(&q->notFull, &q->lock); // Wait until there is space in the queue
    }
    task->next = NULL; // Ensure the new task's next pointer is NULL
    if (q->tail == NULL) {
        q->head = task;
        q->tail = task;
    } else {
        q->tail->next = task;
        q->tail = task;
    }
    q->size++;
    pthread_cond_signal(&q->notEmpty); // Signal that the queue is not empty
    pthread_mutex_unlock(&q->lock);
}

task_t *queue_pop (task_queue_t *q){
    pthread_mutex_lock(&q->lock); // Lock the queue for thread safety
    while (q->size == 0) {
        pthread_cond_wait(&q->notEmpty, &q->lock); // Wait until there is a task in the queue
    }
    task_t *task = q->head; // Remove the head task from the queue
    q->head = task->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }
    q->size--;
    task->next = NULL; // Detach the popped task from the queue list
    pthread_cond_signal(&q->notFull); // Signal that there is space in the queue
    pthread_mutex_unlock(&q->lock);
    return task;
}

void queue_destroy (task_queue_t *q){
    pthread_mutex_lock(&q->lock); // Lock the queue for thread safety
    task_t *current = q->head;
    while (current != NULL) {
        task_t *temp = current;
        current = current->next;
        free(temp); // Free each task in the queue
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    pthread_mutex_unlock(&q->lock);
    pthread_mutex_destroy(&q->lock);
    pthread_cond_destroy(&q->notEmpty);
    pthread_cond_destroy(&q->notFull);
}