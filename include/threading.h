#pragma once

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

typedef struct Thread {
#ifdef WIN32
    HANDLE handle;
    DWORD id;
#else
    pthread_t handle;
#endif
} Thread;

#ifdef WIN32
void thread_init(Thread *thread, LPTHREAD_START_ROUTINE fn, void *arg);
#else
void thread_init(Thread *thread, void * (*fn) (void *), void *arg);
#endif
void thread_join(Thread *thread);
