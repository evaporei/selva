#pragma once

#include "primitives.h"

#include <stdatomic.h>
#include <stddef.h>
#include <stdbool.h>

// TODO: parameterize
#define QUEUE_MAX 5

typedef struct LockFreeQueue {
    // TODO: parameterize
    i32 buffer[QUEUE_MAX];
    _Atomic size_t head;
    _Atomic size_t tail;
} LockFreeQueue;

void lock_free_queue_init(LockFreeQueue *queue);

void lock_free_queue_enqueue(LockFreeQueue *queue, i32 *data);

bool lock_free_queue_dequeue(LockFreeQueue *queue, i32 *data);
