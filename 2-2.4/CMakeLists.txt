cmake_minimum_required(VERSION 3.25)
project(2_2_4 C)

set(CMAKE_C_STANDARD 11)

#Add X11
find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

#Bring the Point into the project
include_directories(src/common)

file(GLOB SOURCES "src/*.c")

add_executable(2_2_4 src/main.c)
target_link_libraries(2_2_4 ${X11_LIBRARIES})
target_link_libraries(2_2_4 m)
