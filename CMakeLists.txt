cmake_minimum_required(VERSION 3.15)
project(PraktikumProject C)
set(CMAKE_C_STANDARD 11)
SET(CMAKE_CXX_FLAGS -pthread)
find_package(Threads REQUIRED)


add_executable(PraktikumProject Praktikum8/a1.c)
target_link_libraries(PraktikumProject Threads::Threads)