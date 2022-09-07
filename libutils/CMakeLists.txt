cmake_minimum_required(VERSION 3.5)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
#add_library(utils_shared SHARED
 #       include/libutils/io.h
  #      src/io.cpp)
add_library(utils_shared SHARED include/libutils/io.h src/io.cpp)
#add_library(utils_static STATIC
 #       include/libutils/io.h
  #      src/io.cpp)
add_library(utils_static STATIC include/libutils/io.h src/io.cpp )

target_include_directories(utils_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )
target_include_directories(utils_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )