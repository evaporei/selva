#pragma once

#include "primitives.h"

#define FatPtr(type, max_size)  \
                                \
    struct {                    \
        usize len;              \
        type data[max_size];    \
    }
                                               
#define fat_ptr_push(ptr, item) \
    ptr->data[ptr->len++] = item;
