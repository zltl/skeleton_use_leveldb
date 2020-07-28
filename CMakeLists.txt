cmake_minimum_required(VERSION 3.8)

project(leveldb-demo)

# This project can use C11, but will gracefully decay down to C89.
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED OFF)
set(CMAKE_C_EXTENSIONS OFF)

# This project requires C++11.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# function to download external projects from git, need to edit cmake/xxxxx
function(my_download_external_project PROJECT_NAME)
  configure_file("cmake/CMakeLists.${PROJECT_NAME}.in"
                 "${PROJECT_NAME}-download/CMakeLists.txt")
  execute_process(
    COMMAND ${CMAKE_COMMAND}
            -G
            "${CMAKE_GENERATOR}"
            .
    RESULT_VARIABLE result
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-download")
  if(result)
    message(FATAL_ERROR "CMake step for ${PROJECT_NAME} failed: ${result}")
  endif()
  execute_process(
    COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-download")
  if(result)
    message(FATAL_ERROR "Build step for ${PROJECT_NAME} failed: ${result}")
  endif()
endfunction(my_download_external_project)

my_download_external_project("leveldb")
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/leveldb-src
                 ${CMAKE_CURRENT_BINARY_DIR}/leveldb-build)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/leveldb-src/include)

find_package(Threads REQUIRED)

file(GLOB
     SK_SOUCE_FILE
     "*.h"
     "*.cc")

add_executable(skeleton_use_leveldb "${SK_SOUCE_FILE}")
target_link_libraries(skeleton_use_leveldb leveldb Threads::Threads)
