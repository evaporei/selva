#pragma once

#include "primitives.h"

#include <stddef.h>
#include <stdbool.h>

#ifdef _WIN32
#include <Windows.h>
#define ATOMIC_VAR(type) volatile type
#define atomic_init(var, val) (*(var) = (val))
#define atomic_load(var) (*(var))
#define atomic_store(var, val) (*(var) = (val))
#define atomic_fetch_add(var, val) InterlockedExchangeAdd((LONG volatile *)(var), (val))
#else
#include <stdatomic.h>
#define ATOMIC_VAR(type) _Atomic type
#endif

// mayybe parameterize
// though there's wrap around
#define QUEUE_MAX 16

#define LockFreeQueue(type) \
    typedef struct type##LockFreeQueue { \
        type buffer[QUEUE_MAX]; \
        ATOMIC_VAR(size_t) head; \
        ATOMIC_VAR(size_t) tail; \
    } type##LockFreeQueue;

#define lock_free_queue_init(queue) \
    atomic_init(&(queue)->head, 0); \
    atomic_init(&(queue)->tail, 0)

#define lock_free_queue_enqueue(queue, data) \
    do { \
        size_t tail = atomic_load(&(queue)->tail); \
        (queue)->buffer[tail % QUEUE_MAX] = *data; \
        atomic_store(&(queue)->tail, tail + 1); \
    } while (0)

#define lock_free_queue_dequeue(queue, retval, data) \
    do { \
        *(retval) = false; \
        size_t head = atomic_load(&(queue)->head); \
        size_t tail = atomic_load(&(queue)->tail); \
        if (head != tail) { \
            *(data) = (queue)->buffer[head % QUEUE_MAX]; \
            atomic_store(&(queue)->head, head + 1); \
            *(retval) = true; \
        } \
    } while (0)
