cmake_minimum_required(VERSION 3.5)
project(TMP CXX)

set(CMAKE_CXX_STANDARD 17)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_compile_options(/W4 /D_CRT_SECURE_NO_WARNINGS)
endif()
add_subdirectory(libutils)
add_subdirectory(lab-1-encapsulation)
add_subdirectory(lab-2-operators)
add_subdirectory(lab-3-xxx)
add_subdirectory(lab-4-dynamic_polymorphism)
add_subdirectory(lab-6-sorts)
add_subdirectory(lab-8-data_structures)
add_subdirectory(lab-10-graph)



