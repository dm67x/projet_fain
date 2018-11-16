#ifndef SCAN_LINE_FILLING_H
#define SCAN_LINE_FILLING_H

#include "polygon.h"

typedef struct {
    Point min;
    Point max;
} BoundingBox;

BoundingBox get_polygone_bounding_box(Polygone polygone);
char is_inside_polygone(Polygone poly, Point t1, Point t2);
void scan_line_fill(Polygone polygone);

#endif // SCAN_LINE_FILLING_H
