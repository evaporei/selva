#include "selva/primitives.h"
#include "selva/threading.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void thread_fn(void *arg) {
    u32 *n = (u32 *) arg;
    assert(*n == 42);
    *n = 50;
    printf("arg: %d\n", *n);
}

int main() {
    Thread thread;
    // stack is not shared between threads
    // if the main thread dies and the other
    // tries to read stack data, it will be UB
    u32 *arg = malloc(sizeof(u32));
    *arg = 42;
    thread_init(&thread, &thread_fn, arg);
    printf("before join\n");
    thread_join(&thread);
    /* thread_detach(&thread); */
    printf("after join\n");
    assert(*arg == 50);
    free(arg);
}
