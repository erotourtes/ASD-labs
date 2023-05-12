cmake_minimum_required(VERSION 3.25)
project(2_2_6 C)

set(CMAKE_C_STANDARD 11)

#Add X11
find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

add_library(app src/app/app.c src/app/app.h)
add_library(matrix src/matrix/matrix.c src/matrix/matrix.h)
add_library(list src/Utils/list.c src/Utils/list.h)
add_library(heap src/Utils/MinHeap.c src/Utils/MinHeap.h)
add_library(graph src/graph/graph.c src/graph/graph.h)
add_library(drawing src/drawing/draw_graph.c src/drawing/draw_graph.h src/drawing/graph_coords.c src/drawing/graph_coords.h)

file(GLOB SOURCES "src/*.c")

add_executable(2_2_6 src/main.c)
target_link_libraries(2_2_6 ${X11_LIBRARIES} m)
target_link_libraries(2_2_6 app drawing matrix graph list heap)
