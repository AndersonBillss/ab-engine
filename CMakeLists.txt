cmake_minimum_required(VERSION 3.21)
project(AbEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC_FILES "src/*.cpp")

add_executable(ab_engine ${SRC_FILES})

target_compile_definitions(ab_engine PRIVATE AB_ENGINE_USE_GLFW=1)

if(EMSCRIPTEN)
  set_target_properties(ab_engine PROPERTIES SUFFIX ".html")
  target_compile_definitions(ab_engine PRIVATE WEBGPU_BACKEND_EMSCRIPTEN)

  target_link_options(ab_engine PRIVATE
    "--shell-file" "../../web/shell.html"
    "-sUSE_WEBGPU=1"
    "--closure=1"
    "-sASSERTIONS=1"
    "-sALLOW_MEMORY_GROWTH=1"
    "-sASYNCIFY"
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