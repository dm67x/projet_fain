#ifndef POLYGON_H
#define POLYGON_H

#include "point.h"

struct _polygone {
    struct _polygone * prev;
    struct _polygone * next;
    Point point;
};

typedef struct _polygone * Polygone;

Polygone newPolygon();
Polygone addPointToPolygon(Polygone poly, Point p);
Polygone deletePointFromPolygon(Polygone poly, Polygone * current);
void nextPointFromPolygon(Polygone poly, Polygone * current);
void prevPointFromPolygon(Polygone poly, Polygone * current);
void drawPolygon(Polygone poly);

#endif // POLYGON_H
