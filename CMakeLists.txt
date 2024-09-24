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

add_library(selva STATIC src/core.c)

target_include_directories(selva PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()

add_executable(core_test tests/core_test.c)

target_link_libraries(core_test PRIVATE selva)

add_test(NAME CoreTest COMMAND core_test)
