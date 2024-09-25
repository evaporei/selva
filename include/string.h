#pragma once

#include "primitives.h"

typedef struct String {
    u8 *buffer;
    usize size;
} String;
