cmake_minimum_required(VERSION 3.5)
add_executable(lab-10-graph main.cpp Graph.h Locality.cpp Locality.h)
target_link_libraries(lab-10-graph utils_static)