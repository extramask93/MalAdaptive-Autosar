cmake_minimum_required(VERSION 3.14...3.22)

project(MalAdaptive-Autosar
    VERSION 0.0.1 
    LANGUAGES CXX)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
message("${headers} ${sources}" )
add_library(${PROJECT_NAME} ${headers} ${sources}
    )
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 23
    LINKER_LANGUAGE CXX)

target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/inc>
                         $<INSTALL_INTERFACE:inc/${PROJECT_NAME}-${PROJECT_VERSION}>
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works