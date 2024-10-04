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

typedef struct ThreadData {
    void (*fn) (void *);
    void *arg;
} ThreadData;

void thread_init(Thread *thread, void (*fn) (void *), void *arg);
void thread_join(Thread *thread);
void thread_detach(Thread *thread);
