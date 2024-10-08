#include <stdio.h>
#include <assert.h>

#include "selva/fix_buf.h"

#define MAX_SIZE 5

FixBuf(u8, MAX_SIZE);

int main() {
    u8FixBuf buf = {0};

    for (u8 n = 1; n <= MAX_SIZE; n++) {
        fix_buf_push(&buf, u8, &n);
    }

    /* fat_buf_push(&buf, 6); */
    /* printf("len %llu\n", buf.len); */
    /* printf("sizes %lu\n", sizeof(buf.data) / sizeof(buf.data[0])); */

    assert(buf.data[0] == 1);
    assert(buf.data[1] == 2);
    assert(buf.data[2] == 3);
    assert(buf.data[3] == 4);
    assert(buf.data[4] == 5);

    for (u8 i = 0; i < buf.len; i++) {
        printf("%d\n", buf.data[i]);
    }

    return 0;
}
