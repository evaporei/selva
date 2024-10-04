#pragma once

#include <assert.h>
#include <memory.h>

#include "primitives.h"

#define FixBuf(type, max_size)    \
    typedef struct type##FixBuf { \
        usize len;                \
        type data[max_size];      \
    } type##FixBuf
                                               
#define fix_buf_push(buf, type, item)                                   \
    assert(buf->len <= sizeof(buf->data) / sizeof(type)); \
    memcpy(buf->data + buf->len++, item, sizeof(type))
