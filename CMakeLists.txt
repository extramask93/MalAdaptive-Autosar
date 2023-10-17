cmake_minimum_required(VERSION 3.14...3.22)

project(MalAdaptive-Autosar
    VERSION 0.0.1 
    LANGUAGES CXX)

find_package(automotive-dlt REQUIRED)

set(CMAKE_CXX_LINK_FLAGS "-Wl,-rpath,/home/damian/toolchains/lib64" "-L/home/damian/toolchains/lib64")
set(CMAKE_BUILD_RPATH "/home/damian/toolchains/lib64")
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(${PROJECT_NAME} SHARED ${headers} ${sources}
    )

add_compile_options(-Wall -Wextra -Wpedantic)
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 26
    LINKER_LANGUAGE CXX)

target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
                         $<INSTALL_INTERFACE:src/${PROJECT_NAME}-${PROJECT_VERSION}>
)
target_link_libraries(${PROJECT_NAME} PRIVATE Genivi::dlt)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works


add_executable(${PROJECT_NAME}_test ${CMAKE_CURRENT_SOURCE_DIR}/test/test.cpp)
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}_test PROPERTIES
    CXX_STANDARD 26
    LINKER_LANGUAGE CXX)
target_include_directories(
  ${PROJECT_NAME}_test PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)
