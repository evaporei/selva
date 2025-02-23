#include "selva/threading.h"
#include "selva/primitives.h"

#include <assert.h>
#include <stdlib.h>

#ifdef _WIN32
DWORD WINAPI wrapper_fn(LPVOID arg) {
    ThreadData *data = (ThreadData *) arg;
    data->fn(data->arg);
    return 0;
}
#else
void *wrapper_fn(void *arg) {
    ThreadData *data = (ThreadData *) arg;
    data->fn(data->arg);
    return NULL;
}
#endif

void thread_init(Thread *thread, void (*fn) (void *), void *arg) {
    ThreadData *data = (ThreadData *) malloc(sizeof(ThreadData));
    data->fn = fn;
    data->arg = arg;
#ifdef _WIN32
    thread->handle = CreateThread(NULL, 0, wrapper_fn, data, 0, &thread->id);
    assert(thread->handle);
}
#else
    i32 result = pthread_create(&thread->handle, NULL, wrapper_fn, data);
    assert(result == 0);
#endif
    thread->data = data;
}

void thread_join(Thread *thread) {
#ifdef _WIN32
    WaitForSingleObject(thread->handle, INFINITE);
    CloseHandle(thread->handle);
#else
    i32 result = pthread_join(thread->handle, NULL);
    assert(result == 0);
#endif
    free(thread->data);
}

void thread_detach(Thread *thread) {
#ifdef _WIN32
    WaitForSingleObject(thread->handle, 0);
    CloseHandle(thread->handle);
#else
    i32 result = pthread_detach(thread->handle);
    assert(result == 0);
#endif
}
