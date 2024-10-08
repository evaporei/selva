#include "selva/lock_free_queue.h"

void lock_free_queue_init(LockFreeQueue *queue) {
    atomic_init(&queue->head, 0);
    atomic_init(&queue->tail, 0);
}

void lock_free_queue_enqueue(LockFreeQueue *queue, i32 *data) {
    size_t tail = atomic_load(&queue->tail);
    queue->buffer[tail % QUEUE_MAX] = *data;
    atomic_store(&queue->tail, tail + 1);
}

bool lock_free_queue_dequeue(LockFreeQueue *queue, i32 *data) {
    size_t head = atomic_load(&queue->head);
    size_t tail = atomic_load(&queue->tail);
    if (head == tail) return false;

    *data = queue->buffer[head % QUEUE_MAX];
    atomic_store(&queue->head, head + 1);

    return true;
}
