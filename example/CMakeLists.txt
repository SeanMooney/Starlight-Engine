project (starlight-example CXX)

# warnings are errors but only for debug
# optimise for storage size on release and debug/storage otherwise
set(CMAKE_CXX_FLAGS_DEBUG "-g -Os -Og -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_RELEASE "-Os")

set (EXAMPLE_INCLUDE include/example/game.hpp)
set (EXAMPLE_SRC src/main.cpp src/game.cpp)
add_executable (starlight-example ${EXAMPLE_INCLUDE} ${EXAMPLE_SRC})
set_target_properties(starlight-example PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries (starlight-example LINK_PUBLIC starlight-core)
target_include_directories (starlight-example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders/fragmentShader.glsl
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shaders)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders/vertexShader.glsl
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/shaders)