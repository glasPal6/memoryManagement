cmake_minimum_required(VERSION 3.25)
project(memLinkedList)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(TEST_NAME test)

#-------------------------------
# Test build
#-------------------------------
add_executable(${TEST_NAME}
    src/tests.c
    src/memLinkedList.h
)

target_compile_definitions(${TEST_NAME}
PRIVATE
    MEMMANAGEMENT_LL
)

target_compile_options(${TEST_NAME}
PRIVATE
#     -Wall
#     -Werror
#     -Wextra
)

