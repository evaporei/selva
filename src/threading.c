#include "selva/threading.h"

#include <assert.h>
#include <stdlib.h>

#ifdef WIN32
DWORD WINAPI wrapper_fn(LPVOID arg) {
    ThreadData *data = (ThreadData *) arg;
    data->fn(data->arg);
    free(data);
    return 0;
}
#else
void *wrapper_fn(void *arg) {
    ThreadData *data = (ThreadData *) arg;
    data->fn(data->arg);
    free(data);
    return NULL;
}
#endif

void thread_init(Thread *thread, void (*fn) (void *), void *arg) {
    ThreadData *data = (ThreadData *) malloc(sizeof(ThreadData));
    data->fn = fn;
    data->arg = arg;
#ifdef WIN32
    thread->handle = CreateThread(NULL, 0, wrapper_fn, data, 0, &thread->id);
    assert(thread->handle);
}
#else
    assert(pthread_create(&thread->handle, NULL, wrapper_fn, data) == 0);
}
#endif

void thread_join(Thread *thread) {
#ifdef WIN32
    WaitForSingleObject(thread->handle, INFINITE);
    CloseHandle(thread->handle);
#else
    assert(pthread_join(thread->handle, NULL) == 0);
#endif
}
