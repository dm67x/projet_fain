#ifndef POLYGON_H
#define POLYGON_H

#include "point.h"

typedef struct PolygonePoint {
    struct PolygonePoint * next;
    Point p;
    unsigned int nb; // number of points
} Polygone;

Polygone * newPolygon();
Polygone * addPointToPolygon(Polygone * p, Point pt);
Polygone * popPointFromPolygon(Polygone * p);
void drawPolygon(Polygone * p);

#endif // POLYGON_H
