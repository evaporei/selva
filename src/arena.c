#include "arena.h"

#include <stdlib.h>
#include <assert.h>

// offset starts at 0, and 8 means 64-bits
// ALIGN_UP(offset, 8)
// (0 + 8 - 1) & ~(8 - 1)
// 7 & ~7
// 0
//
// ALIGN_UP(1, 8)
// (1 + 8 - 1) & ~(8 - 1)
// 8 & ~7
// 8
#define ALIGN_UP(n, align) ( (n + align - 1) & ~(align - 1) )

void arena_init(Arena *arena, usize size) {
    arena->buffer = (u8 *) malloc(size);
    assert(arena->buffer);
    arena->offset = 0;
    arena->capacity = size;
}

void *arena_alloc(Arena *arena, usize count) {
    usize aligned_offset = ALIGN_UP(arena->offset, 8);
    assert(aligned_offset + count <= arena->capacity);
    void *ptr = arena->buffer + aligned_offset;
    arena->offset = aligned_offset + count;
    return ptr;
}

void arena_dealloc(Arena *arena, usize count) {
    assert(arena->offset - count >= 0);
    arena->offset -= count;
}

void arena_reset(Arena *arena) {
    arena->offset = 0;
}

void arena_deinit(Arena *arena) {
    assert(arena->buffer);
    free(arena->buffer);
    arena->buffer = NULL;
    arena->capacity = 0;
    arena->offset = 0;
}
