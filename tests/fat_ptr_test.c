#include <stdio.h>
#include <assert.h>

#include "selva/fat_ptr.h"

int main() {
    FatPtr(u8, 5) ptr = {0};

    fat_ptr_push((&ptr), 1);
    fat_ptr_push((&ptr), 2);
    fat_ptr_push((&ptr), 3);
    fat_ptr_push((&ptr), 4);
    fat_ptr_push((&ptr), 5);
    /* fat_ptr_push((&ptr), 6); */
    /* printf("len %llu\n", ptr.len); */
    /* printf("sizes %lu\n", sizeof(ptr.data) / sizeof(ptr.data[0])); */

    assert(ptr.data[0] == 1);
    assert(ptr.data[1] == 2);
    assert(ptr.data[2] == 3);

    for (u8 i = 0; i < ptr.len; i++) {
        printf("%d\n", ptr.data[i]);
    }

    return 0;
}
