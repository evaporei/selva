#include "primitives.h"
#include "threading.h"

#include <assert.h>
#include <stdio.h>

#ifdef WIN32
DWORD WINAPI thread_function(LPVOID arg) {
#else
void *thread_fn(void *arg) {
#endif
    u32 *n = (u32 *) arg;
    assert(*n == 42);
    printf("arg: %d\n", *n);
    return NULL;
}

int main() {
    Thread thread;
    u32 arg = 42;
    thread_init(&thread, &thread_fn, &arg);
    printf("before join\n");
    thread_join(&thread);
    printf("after join\n");
}
