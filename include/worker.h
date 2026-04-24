#ifndef WORKER_H
#define WORKER_H
#include "queue.h"
#include <stddef.h>
#include <pthread.h>

typedef struct worker_t{
    pthread_t worker; 
    task_queue_t queue; // each worker has its own task queue
} worker_t;

void worker_init(worker_t *w, task_queue_t *q); // initializes a worker
void destroy(worker_t *w); //destroys a worker.

#endif