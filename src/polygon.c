#include "polygon.h"
#include <stdlib.h>
#include "bresenham.h"

Polygone * newPolygon() {
    return NULL;
}

Polygone * addPointToPolygon(Polygone * p, Point pt) {
    Polygone * n = (Polygone *)malloc(sizeof(struct PolygonePoint));
    n->next = p;
    n->p = pt;
    return n;
}

Polygone * popPointFromPolygon(Polygone * p) {
    Polygone * n = p->next;
    free(p);
    return n;
}

void drawPolygon(Polygone * p) {
    if (p == NULL) return;
    Point p1 = p->p;
    p = p->next;

    for (; p != NULL; p = p->next) {
        Point p2 = p->p;
        bresenham(p1, p2);
        p1 = p2;
    }
}
