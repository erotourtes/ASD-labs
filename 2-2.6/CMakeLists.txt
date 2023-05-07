cmake_minimum_required(VERSION 3.25)
project(2_2_5 C)

set(CMAKE_C_STANDARD 11)

#Add X11
find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

add_library(app src/app/app.c src/app/app.h)
add_library(matrix src/matrix/matrix.c src/matrix/matrix.h)
add_library(queue src/Utils/queue.c src/Utils/queue.h)
add_library(drawing src/drawing/draw_graph.c src/drawing/draw_graph.h src/drawing/graph_coords.c src/drawing/graph_coords.h)

file(GLOB SOURCES "src/*.c")

add_executable(2_2_5 src/main.c)
target_link_libraries(2_2_5 ${X11_LIBRARIES} m)
target_link_libraries(2_2_5 app drawing matrix queue)