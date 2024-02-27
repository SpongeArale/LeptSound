cmake_minimum_required(VERSION 3.22)
project(LeptSound)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_LIB_NAME "leptsound")
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/dist)

set(CXX_FLAGS
 -D_FILE_OFFSET_BITS=64
 -Wall
 -Wextra
 -Werror
#  -Wconversion
 -Wno-unused-parameter
#  -Wold-style-cast
 -Woverloaded-virtual
 -Wpointer-arith
 -Wshadow
 -Wwrite-strings
 -march=native
 -rdynamic
 )
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

message(${PROJECT_SOURCE_DIR})
message(STATUS "libleptsound_dir = " ${PROJECT_SOURCE_DIR}/dist)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty/ ${PROJECT_SOURCE_DIR}/include/)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/. PROJECT_SRC)
link_directories(${PROJECT_SOURCE_DIR}/libs/)
add_library(${PROJECT_LIB_NAME} ${PROJECT_SRC})
target_link_libraries(${PROJECT_LIB_NAME} IrrKlang)
