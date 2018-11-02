#ifndef POLYGON_H
#define POLYGON_H

#include "point.h"

typedef struct PolygonePoint {
    struct PolygonePoint * next;
    struct PolygonePoint * prev;
	Point p;
	int closed_index;
} *Polygone;

Polygone newPolygon();
Polygone addPointToPolygon(Polygone p, int index, Point pt);
Polygone deletePointFromPolygon(Polygone p, int index);
Point getPointFromPolygon(Polygone p, int index);
void updatePointFromPolygone(Polygone p, int index, Point pt);
int sizePolygon(Polygone p);
void drawPolygon(Polygone p);

#endif // POLYGON_H
