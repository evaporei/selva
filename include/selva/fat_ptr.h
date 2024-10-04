#pragma once

#ifdef DEBUG
#include <assert.h>
#endif
#include <memory.h>

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
    memcpy(ptr->data + ptr->len++, item, sizeof(ptr->data[0]))
#else
#define fat_ptr_push(ptr, item) \
    ptr->data[ptr->len++] = item
#endif
