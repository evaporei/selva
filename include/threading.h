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

void thread_init(Thread *thread, void * (*fn) (void *), void *arg);
void thread_join(Thread *thread);
