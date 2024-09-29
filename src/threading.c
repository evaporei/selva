#include "threading.h"

#include <assert.h>

#ifdef WIN32
void thread_init(Thread *thread, LPTHREAD_START_ROUTINE fn, void *arg) {
    thread->handle = CreateThread(NULL, 0, fn, arg, 0, &thread->id);
    assert(thread->handle);
}
#else
void thread_init(Thread *thread, void * (*fn) (void *), void *arg) {
    assert(pthread_create(&thread->handle, NULL, fn, arg) == 0);
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
