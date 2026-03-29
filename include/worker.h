#ifndef WORKER_H
#define WORKER_H
#include "queue.h"
#include <stddef.h>
#include <pthread.h>

typedef struct worker_t{
    pthread_t worker; 
    task_queue_t queue;
} worker_t;

void worker_init(worker_t *w);
void destroy(worker_t *w);

#endif