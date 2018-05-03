project (starlight-example CXX)
# Add executable called "helloDemo" that is built from the source files
# "demo.cxx" and "demo_b.cxx". The extensions are automatically found.
add_executable (starlight-example src/main.cpp)
set_target_properties(starlight-example PROPERTIES LINKER_LANGUAGE CXX)
# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
# helloDemo
target_link_libraries (starlight-example LINK_PUBLIC starlight-core)
