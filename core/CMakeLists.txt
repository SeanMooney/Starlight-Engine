
project (starlight-core CXX)
# Create a library called "core" which includes the header file "core.hpp".
# The extension is already found. Any number of sources could be listed here.
set (CORE_INCLUDE_files include/core/core.hpp  include/core/gfx/gfx.hpp
     include/core/gfx/gl.hpp include/core/gfx/window.hpp include/core/gfx/glfw.hpp
     include/core/input/keyboard.hpp include/core/input/mouse.hpp
     include/core/input/manager.hpp)

     set (CORE_SRC src/gfx/window.cpp src/gfx/glfw.cpp 
          src/input/keyboard.cpp src/input/mouse.cpp src/input/manager.cpp) 


add_library (starlight-core ${CORE_INCLUDE} ${CORE_SRC})
set_target_properties(starlight-core PROPERTIES LINKER_LANGUAGE CXX)
# Make sure the compiler can find include files for our core library
# when other libraries or executables link to core
target_include_directories (starlight-core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(GenerateExportHeader)
GENERATE_EXPORT_HEADER( starlight-core
             BASE_NAME starlight-core
             EXPORT_MACRO_NAME STARLIGHTAPI
             EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/include/core/starlightapi.hpp
             STATIC_DEFINE STARLIGHTAPI_BUILT_AS_STATIC
)

include(${CMAKE_CURRENT_SOURCE_DIR}/../external/vcpkg/scripts/buildsystems/vcpkg.cmake)

set (EXTERNAL_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../external/vcpkg/installed/x64-linux)

add_library(glew STATIC IMPORTED)
set_target_properties(glew PROPERTIES
IMPORTED_LOCATION "${EXTERNAL_ROOT}/lib/libGLEW.a"
INTERFACE_INCLUDE_DIRECTORIES "${EXTERNAL_ROOT}/include/GL"
)

add_library(glfw3 STATIC IMPORTED)
set_target_properties(glfw3 PROPERTIES
IMPORTED_LOCATION "${EXTERNAL_ROOT}/lib/libglfw3.a"
INTERFACE_INCLUDE_DIRECTORIES "${EXTERNAL_ROOT}/include/GLFW"
)

target_include_directories(starlight-core PUBLIC
    ${EXTERNAL_ROOT}/vcpkg/installed/x64-linux/gsl/include)

find_package(cereal REQUIRED)
set (GL_LINKS GL GLU X11 Xxf86vm Xrandr pthread Xi Xcursor Xinerama m dl )
target_link_libraries (starlight-core LINK_PUBLIC ${GL_LINKS} cereal glew glfw3)