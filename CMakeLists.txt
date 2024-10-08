cmake_minimum_required(VERSION 3.22)
project(selva VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)

# Enable Clangd LSP integration with the project
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------------------------------------------
# Source files
# ------------------------------------------------------------------------------

set(MY_FLAGS "-std=c11" "-Wall")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(selva STATIC
    src/arena.c
    src/threading.c
    src/lock_free_queue.c
)

target_include_directories(selva PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()

add_executable(arena_test tests/arena_test.c)
target_link_libraries(arena_test PRIVATE selva)
add_test(NAME ArenaTest COMMAND arena_test)

add_executable(threading_test tests/threading_test.c)
target_link_libraries(threading_test PRIVATE selva)
add_test(NAME ThreadingTest COMMAND threading_test)

add_executable(fix_buf_test tests/fix_buf_test.c)
target_link_libraries(fix_buf_test PRIVATE selva)
add_test(NAME FixBufTest COMMAND fix_buf_test)

add_executable(lock_free_queue_test tests/lock_free_queue_test.c)
target_link_libraries(lock_free_queue_test PRIVATE selva)
add_test(NAME LockFreeQueueTest COMMAND lock_free_queue_test)
