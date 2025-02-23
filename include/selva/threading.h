#pragma once

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

typedef struct ThreadData {
    void (*fn) (void *);
    void *arg;
} ThreadData;

typedef struct Thread {
#ifdef _WIN32
    // order relevant because of padding
    // https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4820?view=msvc-170
    DWORD id;
    HANDLE handle;
#else
    pthread_t handle;
#endif
    ThreadData *data;
} Thread;

void thread_init(Thread *thread, void (*fn) (void *), void *arg);
void thread_join(Thread *thread);
void thread_detach(Thread *thread);
