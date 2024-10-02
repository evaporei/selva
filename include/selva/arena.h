#pragma once

#include "primitives.h"

typedef struct Arena {
    u8 *buffer;
    usize capacity;
    usize offset;
} Arena;

void arena_init(Arena *arena, usize size);

void *arena_alloc(Arena *arena, usize count);

void arena_dealloc(Arena *arena, usize count);

void arena_reset(Arena *arena);

void arena_deinit(Arena *arena);
