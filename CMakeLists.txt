cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

set (CMAKE_C_FLAGS "--std=gnu99 ${CMAKE_C_FLAGS}")

project(cubesat)

add_executable(test_orbit_data src/main.c src/CubeSat.c)
target_link_libraries(test_orbit_data m)
