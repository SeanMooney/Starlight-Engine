project (starlight-test CXX)
set (EXTERNAL_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../external)
set (PKG_ROOT ${EXTERNAL_ROOT}/vcpkg/packages)
include_directories(${PKG_ROOT}/catch ${EXTERNAL_ROOT}/fakeit/include
                    ${EXTERNAL_ROOT}/fakeit/single_header/standalone)
set(TEST_SRC_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_SOURCES ${TEST_SRC_PREFIX}/main.cpp ${TEST_SRC_PREFIX}/core/input/mouse.cpp
    ${TEST_SRC_PREFIX}/core/input/keyboard.cpp ${TEST_SRC_PREFIX}/core/input/manager.cpp
    ${EXTERNAL_ROOT}/fakeit/single_header/standalone/fakeit.hpp)

add_executable(starlight-test ${TEST_SOURCES})

set_target_properties(starlight-test PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories (starlight-test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries (starlight-test LINK_PUBLIC starlight-core)
