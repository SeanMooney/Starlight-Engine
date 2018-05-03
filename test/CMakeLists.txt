project (starlight-test CXX)
# Create a library called "core" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
#add_library (starlight-test include/test/shared.hpp)
include(${CMAKE_CURRENT_SOURCE_DIR}/../external/vcpkg/scripts/buildsystems/vcpkg.cmake)
find_path(CATCH_INCLUDE_DIR catch.hpp)
include_directories(${CATCH_INCLUDE_DIR})

set(TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
add_executable(starlight-test ${TEST_SOURCES})
set_target_properties(starlight-test PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories (starlight-test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries (starlight-test LINK_PUBLIC starlight-core)
