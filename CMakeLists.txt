cmake_minimum_required (VERSION 3.8)
project (starlight-engine CXX)
set (CMAKE_CXX_STANDARD 17)

add_subdirectory (core)
add_subdirectory (test)
add_subdirectory (example)

#set up default compiler flags
# warnings are errors but only for debug
# optimise for storage size on release and debug/storage otherwise
set(CMAKE_CXX_FLAGS_DEBUG "-g -Os -Og -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_RELEASE "-Os")


if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt." )
endif()

