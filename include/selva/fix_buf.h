#pragma once

#ifdef DEBUG
#include <assert.h>
#endif
#include <memory.h>

#include "primitives.h"

#define FixBuf(type, max_size)    \
    typedef struct type##FixBuf { \
        usize len;                \
        type data[max_size];      \
    } type##FixBuf
                                               
#ifdef DEBUG
#define fix_buf_push(buf, item)                                   \
    assert(buf->len <= sizeof(buf->data) / sizeof(buf->data[0])); \
    memcpy(buf->data + buf->len++, item, sizeof(buf->data[0]))
#else
#define fix_buf_push(buf, item) \
    memcpy(buf->data + buf->len++, item, sizeof(buf->data[0]))
#endif
