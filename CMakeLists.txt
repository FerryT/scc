cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(SCC)

add_library(scc src/scc.cpp src/tarjan.cpp src/ges.cpp)
target_include_directories(scc PUBLIC include)

add_executable(scc-cli src/main.cpp src/aut.cpp src/dot.cpp)
target_link_libraries(scc-cli PRIVATE scc)
