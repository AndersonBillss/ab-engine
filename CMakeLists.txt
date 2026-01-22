cmake_minimum_required(VERSION 3.21)
project(AbEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ab_engine
  src/main.cpp
)

target_compile_definitions(ab_engine PRIVATE AB_ENGINE_USE_GLFW=1)

if(EMSCRIPTEN)
  set_target_properties(ab_engine PROPERTIES SUFFIX ".html")

  target_link_options(ab_engine PRIVATE
    "-sUSE_WEBGPU=1"
    "-sASSERTIONS=1"
    "-sALLOW_MEMORY_GROWTH=1"
  )

else()
  add_subdirectory(third_party/dawn/third_party/glfw)

  list(PREPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/build/_install/dawn/debug")
  find_package(Dawn CONFIG REQUIRED)
  find_package(Threads REQUIRED)

  target_link_libraries(ab_engine PRIVATE
    dawn::webgpu_dawn
    glfw
  )
endif()