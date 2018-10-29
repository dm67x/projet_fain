#ifndef SCAN_LINE_FILLING_H
#define SCAN_LINE_FILLING_H

#include "polygon.h"

void find_min_max(Polygone * polygone, Point * min, Point * max);
void find_intersections(Polygone * polygone, Point * intersections);
void scan_line_fill(Polygone * polygone);

#endif // SCAN_LINE_FILLING_H
