cmake_minimum_required(VERSION 3.21)
project(AbEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

# Link Dawn 
list(PREPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/build/_install/dawn/debug")
find_package(Dawn CONFIG REQUIRED)

# Link GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(third_party/dawn/third_party/glfw)

# Add project files
add_executable(ab_engine
  src/main.cpp
)

target_compile_definitions(ab_engine PRIVATE AB_ENGINE_USE_GLFW=1)

target_link_libraries(ab_engine PRIVATE
  dawn::webgpu_dawn
  glfw
)
