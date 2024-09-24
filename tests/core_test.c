#include <stdio.h>
#include "core.h"

int main() {
    int result = add(2, 3);
    if (result == 5) {
        printf("Test passed!\n");
        return 0;
    } else {
        printf("Test failed: expected 5, got %d\n", result);
        return 1;
    }
}
