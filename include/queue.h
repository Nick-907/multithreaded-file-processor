#ifndef QUEUE_H
#define QUEUE_H
#include <stddef.h>
#include <pthread.h>

typedef struct task_t{
    void(*fn) (void *arg);
    void *arg;
    struct task_t *next;

} task_t;

typedef struct task_queue_t{
    task_t * head;
    task_t * tail;
    size_t size;
    size_t capacity;
    pthread_mutex_t lock; // prevetns multiple threads from accessing the data at the same time. 
    pthread_cond_t notEmpty;
    pthread_cond_t notFull; 

}task_queue_t;

void queue_init(task_queue_t *q, size_t capacity);//initializes a queue
void queue_push(task_queue_t *q,task_t *task); //pushes a task in the queue
void queue_pop(task_queue_t *q); // pops a  task from the queue
void queue_destroy(task_queue_t *q); // destroys a queue
#endif