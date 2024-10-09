#include "selva/selva.h"

#include <stdio.h>

LockFreeQueue(i32);

// needs to be global (data segment)
// or in the heap
//
// stack is not shared between threads
i32LockFreeQueue queue = {0};

void main_thread() {
    usize count = 0;
    i32 element;
    while (count < QUEUE_MAX) {
        if (lock_free_queue_dequeue(&queue, &element)) {
            printf("main:element %d\n", element);
            count += 1;
        }
    }
}

void secondary_thread() {
    for (i32 n = 1; n <= QUEUE_MAX; n++) {
        lock_free_queue_enqueue(&queue, &n);
    }
}

int main() {
    lock_free_queue_init(&queue);

    Thread thread;
    thread_init(&thread, secondary_thread, NULL);

    main_thread();

    thread_join(&thread);

    return 0;
}
