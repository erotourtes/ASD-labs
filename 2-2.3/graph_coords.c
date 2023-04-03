void top_row(int num_in_row, Point *cur_point, Point *points, double distance, int *cur, int rest);

void right_column(int num_in_row, Point *cur_point, Point *points, int distance, int *cur, int rest);

void bottom_row(int num_in_row, Point *cur_point, Point *points, int distance, int *cur, int rest);

void left_column(int num_in_row, Point *cur_point, Point *points, int distance, int *cur, int rest);

void center(int num_in_row, Point *point, int distance, int rest);

void copy_point(Point *from, Point *to) {
    to->x = from->x;
    to->y = from->y;
}

Point *get_coordinates(int n, int distance) {
    Point *points = malloc(n * sizeof(Point));

    int k = n - 1; // number of points without center
    int num_in_row = floor((k + 4) / 4);
    int rest = k - (num_in_row * 4 - 4);
    int cur = 0;

    Point cur_point = {-distance, 0};

    center(num_in_row, &points[n-1], distance, rest);
    top_row(num_in_row, &cur_point, points, distance, &cur, rest);
    right_column(num_in_row, &cur_point, points, distance, &cur, rest);
    bottom_row(num_in_row, &cur_point, points, distance, &cur, rest);
    left_column(num_in_row, &cur_point, points, distance, &cur, rest);

    return points;
}

void center(int num_in_row, Point *point, int distance, int rest) {
    point->x = ((num_in_row - 1) * distance + (rest > 1 ? distance : 0)) / 2;
    point->y = ((num_in_row - 1) * distance) / 2;
}

void top_row(int num_in_row, Point *cur_point, Point *points, double distance, int *cur, int rest) {
    if (rest == 1) { // need to compress top row
        distance *= (double) (num_in_row - 1) / (num_in_row);
        cur_point->x = -distance;
        num_in_row++;
    } else if (rest == 2 || rest == 3) {
        num_in_row++;
    }

    for (int i = 0; i < num_in_row; i++) {
        cur_point->x += distance;
        copy_point(cur_point, &points[*cur]);
        (*cur)++;
    }
}

void right_column(int num_in_row, Point *cur_point, Point *points, int distance, int *cur, int rest) {
    if (rest == 3) {
        distance *= (double) (num_in_row - 1) / (num_in_row);
        num_in_row++;
    }
    for (int i = 0; i < num_in_row - 1; i++) {
        cur_point->y += distance;
        copy_point(cur_point, &points[*cur]);
        (*cur)++;
    }
}

void bottom_row(int num_in_row, Point *cur_point, Point *points, int distance, int *cur, int rest) {
    if (rest == 2 || rest == 3) {
        num_in_row++;
    }
    for (int i = 0; i < num_in_row - 1; i++) {
        cur_point->x -= distance;
        copy_point(cur_point, &points[*cur]);
        (*cur)++;
    }
}

void left_column(int num_in_row, Point *cur_point, Point *points, int distance, int *cur, int rest) {
    for (int i = 0; i < num_in_row - 2; i++) {
        cur_point->y -= distance;
        copy_point(cur_point, &points[*cur]);
        (*cur)++;
    }
}
