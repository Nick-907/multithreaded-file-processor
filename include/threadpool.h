#ifndef THREADPOOL_H
#define THREADPOOL_H
#include "worker.h"
#include <stddef.h>

typedef struct threadpool_t{
    worker_t *workers; // array of workers
    size_t num_workers; // number of workers in the pool
    task_queue_t *task_queue; // shared task queue for all workers
    int stop; // flag to indicate if the thread pool should stop
} threadpool_t;

threadpool_t * threadpool_create(size_t num_workers, size_t queue_capacity); // creates a thread pool
void threadpool_submit(threadpool_t *pool, void (*fn)(void *), void *arg); // submits a task to the thread pool
void threadpool_destroy(threadpool_t *pool); // destroys the thread pool
void threadpool_shutdown(threadpool_t *pool); // shuts down the thread pool gracefully


#endif