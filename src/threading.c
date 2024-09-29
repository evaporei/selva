#include "threading.h"

#include <assert.h>

void thread_init(Thread *thread, void * (*fn) (void *), void *arg) {
#ifdef WIN32
    thread->handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) fn, &arg, 0, &thread->id);
    assert(thread->handle);
#else
    assert(pthread_create(&thread->handle, NULL, fn, arg) == 0);
#endif
}

void thread_join(Thread *thread) {
#ifdef WIN32
    WaitForSingleObject(thread->handle, INFINITE);
    CloseHandle(thread->handle);
#else
    assert(pthread_join(thread->handle, NULL) == 0);
#endif
}
