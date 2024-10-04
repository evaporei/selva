#include <stdio.h>
#include <assert.h>

#include "selva/fat_ptr.h"

int main() {
    FatPtr(u8, 5) ptr = {0};

    fat_ptr_push((&ptr), 1);
    fat_ptr_push((&ptr), 2);
    fat_ptr_push((&ptr), 3);

    assert(ptr.data[0] == 1);
    assert(ptr.data[1] == 2);
    assert(ptr.data[2] == 3);

    for (u8 i = 0; i < ptr.len; i++) {
        printf("%d\n", ptr.data[i]);
    }

    return 0;
}
