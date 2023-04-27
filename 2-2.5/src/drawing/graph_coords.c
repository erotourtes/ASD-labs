#include <malloc.h>
#include <math.h>
#include "graph_coords.h"

void copy_point(Point *from, Point *to) {
    to->x = from->x;
    to->y = from->y;
}

void compress(int i, int rest, int *distance, int *num_in_row) {
    if (i == 0) { // top
        if (rest == 1) { // need to compress top row
            *distance *= (*num_in_row - 1) / (*num_in_row);
            (*num_in_row)++;
        } else if (rest == 2 || rest == 3) {
            (*num_in_row)++;
        }
    }

    if (i == 1 && rest == 3) { // right
        *distance *= (*num_in_row - 1) / (*num_in_row);
        (*num_in_row)++;
    }

    if (i == 2 && (rest == 2 || rest == 3)) { // bottom
        (*num_in_row)++;
    }
}

Point *get_coordinates(int n, int distance) {
    Point *points = malloc(n * sizeof(Point));

    int k = n - 1; // number of points without center
    int num_in_row = floor((k + 4.0) / 4);
    int rest = k % 4;

    int directions[][2] = {{1,  0},
                           {0,  1},
                           {-1, 0},
                           {0,  -1}};

    Point cur_point = {0, 0};
    int cur = 0;
    for (int i = 0; i < 4; i++) {
        int cur_distance = distance;
        int cur_num_in_row = num_in_row;

        compress(i, rest, &cur_distance, &cur_num_in_row);

        for (int j = 1; j < cur_num_in_row; j++) {
            copy_point(&cur_point, &points[cur++]);
            cur_point.x += directions[i][0] * cur_distance;
            cur_point.y += directions[i][1] * cur_distance;
        }
    }

    points[cur].x = ((num_in_row - 1) * distance + (rest > 1 ? distance : 0)) / 2.0;
    points[cur].y = ((num_in_row - 1) * distance) / 2.0;

    return points;
}