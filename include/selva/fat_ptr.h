#pragma once

#ifdef DEBUG
#include <assert.h>
#endif

#include "primitives.h"

#define FatPtr(type, max_size)  \
                                \
    struct {                    \
        usize len;              \
        type data[max_size];    \
    }
                                               
#ifdef DEBUG
#define fat_ptr_push(ptr, item)                                   \
    assert(ptr->len <= sizeof(ptr->data) / sizeof(ptr->data[0])); \
    ptr->data[ptr->len++] = item
#else
#define fat_ptr_push(ptr, item) \
    ptr->data[ptr->len++] = item
#endif
