
project (starlight-core CXX)
# Create a library called "core" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
add_library (starlight-core include/core/core.hpp)
set_target_properties(starlight-core PROPERTIES LINKER_LANGUAGE CXX)
# Make sure the compiler can find include files for our core library
# when other libraries or executables link to core
target_include_directories (starlight-core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
