#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "arena.h"

int main() {
    Arena arena;
    arena_init(&arena, sizeof(u8) * 64);
    assert(arena.offset == 0);
    assert(arena.capacity == sizeof(u8) * 64);

    u8 *list = (u8 *) arena_alloc(&arena, sizeof(u8) * 5);
    assert(list);
    assert(arena.buffer == list);
    assert(arena.offset == sizeof(u8) * 5);

    for (u8 i = 0; i < 5; i++)
        list[i] = i + 1;

    printf("[ ");
    for (u8 i = 0; i < 5; i++)
        printf("%d ", list[i]);
    printf("]\n");

    char *str = (char *) arena_alloc(&arena, sizeof(char) * 6);
    assert(str);
    assert(arena.buffer + sizeof(u8) * 8 == (u8 *) str);
    assert(arena.offset == sizeof(u8) * 8 + sizeof(char) * 6);

    strcpy(str, "hello");

    printf("%s\n", str);

    arena_dealloc(&arena, sizeof(char) * 6);
    assert(arena.buffer + sizeof(u8) * 8 == (u8 *) str);
    assert(arena.offset == sizeof(u8) * 8);

    str = (char *) arena_alloc(&arena, sizeof(char) * 6);
    assert(str);
    assert(arena.buffer + sizeof(u8) * 8 == (u8 *) str);
    assert(arena.offset == sizeof(u8) * 8 + sizeof(char) * 6);

    strcpy(str, "banana");

    printf("%s\n", str);

    arena_reset(&arena);
    assert(arena.offset == 0);

    list = (u8 *) arena_alloc(&arena, sizeof(u8) * 10);
    assert(list);
    assert(arena.buffer == list);
    assert(arena.offset == sizeof(u8) * 10);

    for (u8 i = 0; i < 10; i++)
        list[i] = i + 1;

    printf("[ ");
    for (u8 i = 0; i < 10; i++)
        printf("%d ", list[i]);
    printf("]\n");

    arena_deinit(&arena);
    assert(arena.buffer == NULL);
    assert(arena.offset == 0);
    assert(arena.capacity == 0);
}
