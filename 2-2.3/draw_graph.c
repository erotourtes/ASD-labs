void applyOffset(Point *points, int n, int offset) {
    for (int i = 0; i < n; i++) {
        points[i].x += offset;
        points[i].y += offset;
    }
}

void draw_nodes(X11 app, Point *points, int len, int circle_radius, unsigned long bg, unsigned long fg) {
    int ch_x_offset = 3;
    int ch_y_offset = 5;

    for (int i = 0; i < len; i++) {
        XSetForeground(app.dis, app.gc, bg);

        XFillArc(app.dis, app.win, app.gc, points[i].x - circle_radius, points[i].y - circle_radius,
                 circle_radius * 2, circle_radius * 2, 0, 360 * 64);

        XSetForeground(app.dis, app.gc, fg);
        char name[2];
        sprintf(name, "%d", i + 1);
        XDrawString(app.dis, app.win, app.gc, points[i].x - ch_x_offset, points[i].y + ch_y_offset, name,
                    (i < 9 ? 1 : 2));
    }
}

int is_through_center(Point *p, int i, int j, int n) {
    Point p1 = p[i];
    Point p2 = p[j];
    Point center = p[n - 1];
    return (p1.x + p2.x) / 2 == center.x && (p1.y + p2.y) / 2 == center.y;
}

int in_range(int x, int a, int b) {
    return a < x && x < b || b < x && x < a;
}

int is_overlapping(Point *points, int n, int i, int j) {
    Point p1 = points[i];
    Point p2 = points[j];

    for (int k = 0; k < n; k++) {
        if (k == i || k == j) continue;

        Point cur = points[k];
        int is_in_row = p1.y == p2.y && p1.y == cur.y && in_range(cur.x, p1.x, p2.x);
        int is_in_column = p1.x == p2.x && p1.x == cur.x && in_range(cur.y, p1.y, p2.y);
        if (is_in_row || is_in_column)
            return 1;
    }

    return 0;
}

int is_arrows_overlaps(Matrix matrix, int i, int j) {
    int **m = matrix.val;

    return m[i][j] && m[j][i];
}

void draw_head_arrow(X11 app, Point p, float deg) {
    float fi = M_PI / 180.0 * (180.0 - deg);
    float arrow_angle = 0.3;
    int len = 15;

    int lx = p.x + len * cos(fi + arrow_angle);
    int rx = p.x + len * cos(fi - arrow_angle);
    int ly = p.y + len * sin(fi + arrow_angle);
    int ry = p.y + len * sin(fi - arrow_angle);

    XDrawLine(app.dis, app.win, app.gc, lx, ly, p.x, p.y);
    XDrawLine(app.dis, app.win, app.gc, rx, ry, p.x, p.y);
}

void draw_loop(X11 app, int circle_radius, Point p) {
    int arc_width = circle_radius * 1.5;
    int arc_height = circle_radius * 1.5;
    XDrawArc(app.dis, app.win, app.gc, p.x - circle_radius - arc_width / 2, p.y - arc_height, arc_width, arc_height,
             0 * 64,
             360 * 64);

    Point arrow_point = {p.x - circle_radius, p.y};
    draw_head_arrow(app, arrow_point, -15);
}

void draw_arrow_line(X11 app, Point p1, Point p2, double circle_radius) {
    double dy = -(p2.y - p1.y);
    double dx = (p2.x - p1.x);
    double angle = atan(dy / dx);

    int to_left = p1.x > p2.x; // to left (left top; left bottom)
    if (to_left) {
        Point p = {p2.x + circle_radius * cos(angle), p2.y - circle_radius * sin(angle)};
        draw_head_arrow(app, p, 180 + angle * 180 / M_PI);
    } else { // to right (right top; right bottom) && top && bottom
        Point p = {p2.x - circle_radius * cos(angle), p2.y + circle_radius * sin(angle)};
        draw_head_arrow(app, p, angle * 180 / M_PI);
    }

    XDrawLine(app.dis, app.win, app.gc, p1.x, p1.y, p2.x, p2.y);
}

void draw_through_angle(X11 app, Point *points, int i, int j, int circle_radius) {
    int mid_x = (points[i].x + points[j].x) / 2;
    int mid_y = (points[i].y + points[j].y) / 2;

    int offsetX = 2.5 * circle_radius;
    int offsetY = 2.5 * circle_radius;

    double c = sqrt(pow(mid_x - points[i].x, 2) + pow(mid_y - points[i].y, 2));
    double angle = atan2((double) offsetX, c);

    // flip in opposite direction
    if (points[i].x > points[j].x && points[i].y > points[j].y) {
        offsetX = -offsetX;
        offsetY = -offsetY;
        // not to overlap with other lines which is dense to each other
    } else if (points[i].x < points[j].x && points[i].y > points[j].y) {
        offsetY = -2 * offsetY;
        offsetX = 1.5 * offsetX;
    } else if (points[i].x > points[j].x && points[i].y < points[j].y) {
        offsetY = 2 * offsetY;
        offsetX = -1.5 * offsetX;
    }

    Point middle = {mid_x - offsetX * cos(angle), mid_y + offsetY * sin(angle)};

    XDrawLine(app.dis, app.win, app.gc, points[i].x, points[i].y, middle.x, middle.y);
    draw_arrow_line(app, middle, points[j], circle_radius);
}

void draw_row_overlap(X11 app, Point *points, int i, int j, int circle_radius) {
    int mid_x = (points[i].x + points[j].x) / 2;

    int dx = abs(points[i].x - points[j].x);
    int offset = circle_radius / 2 + log10(dx) * 10;

    if (points[i].x > points[j].x)
        offset *= -1;

    Point middle = {mid_x, points[i].y + offset};
    XDrawLine(app.dis, app.win, app.gc, points[i].x, points[i].y, middle.x, middle.y);
    draw_arrow_line(app, middle, points[j], circle_radius);
}

void draw_column_overlap(X11 app, Point *points, int i, int j, int circle_radius) {
    int mid_y = (points[i].y + points[j].y) / 2;

    int dy = abs(points[i].y - points[j].y);
    int offset = circle_radius / 2 + log10(dy) * 10;

    if (points[i].y > points[j].y)
        offset *= -1;

    Point middle = {points[i].x + offset, mid_y};
    XDrawLine(app.dis, app.win, app.gc, points[i].x, points[i].y, middle.x, middle.y);
    draw_arrow_line(app, middle, points[j], circle_radius);
}

void draw_overlapping(X11 app, Point *points, int i, int j, int circle_radius) {
    if (points[i].y == points[j].y)
        draw_row_overlap(app, points, i, j, circle_radius);
    else if (points[i].x == points[j].x)
        draw_column_overlap(app, points, i, j, circle_radius);
    else
        draw_through_angle(app, points, i, j, circle_radius);
}

void draw_graph(X11 app, Matrix matrix) {
    Point *points = get_coordinates(matrix.n, 100);
    int offset = 100;
    applyOffset(points, matrix.n, offset);

    int circle_radius = 20;
    unsigned long blue = 0x83c9f4;
    unsigned long dark = 0x2b061e;

    XSetLineAttributes(app.dis, app.gc, 2, LineSolid, CapButt, JoinMiter);

    for (int i = 0; i < matrix.n; i++) {
        for (int j = 0; j < matrix.n; j++) {
            if (matrix.val[i][j] == 0) continue;

            if (i == j)
                draw_loop(app, circle_radius, (Point) {points[i].x, points[i].y});
            else if (is_through_center(points, i, j, matrix.n))
                draw_through_angle(app, points, i, j, circle_radius);
            else if (is_overlapping(points, matrix.n, i, j) || is_arrows_overlaps(matrix, i, j))
                draw_overlapping(app, points, i, j, circle_radius);
            else
                draw_arrow_line(app, points[i], points[j], circle_radius);
        }
    }

    draw_nodes(app, points, matrix.n, circle_radius, blue, dark);

    free(points);
}