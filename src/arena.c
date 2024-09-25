#include "arena.h"

#include <stdlib.h>
#include <assert.h>

void arena_init(Arena *arena, usize size) {
    arena->buffer = (u8 *) malloc(size);
    assert(arena->buffer);
    arena->offset = 0;
    arena->capacity = size;
}

void *arena_alloc(Arena *arena, usize count) {
    void *ptr = arena->buffer + arena->offset;
    arena->offset += count;
    return ptr;
}

void arena_dealloc(Arena *arena, usize count) {
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
