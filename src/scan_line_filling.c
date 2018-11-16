#if WIN32
#include <windows.h>
#endif

#include "scan_line_filling.h"
#include <stdlib.h>
#include <GL/gl.h>
#include "color.h"
#include <math.h>
#include <stdio.h>

BoundingBox get_polygone_bounding_box(Polygone polygone) {
    int padding = 2;
    BoundingBox bb;
    bb.min = bb.max = (Point) { -1, -1 };

    if (!polygone.sommets)
        return bb;

    struct _sommet * sommet = polygone.sommets;
    Point p = sommet->point;
    bb.min = bb.max = p;

    sommet = sommet->next;
    while (sommet != polygone.sommets) {
        p = sommet->point;
        if (bb.min.x > p.x) bb.min.x = p.x;
        if (bb.max.x < p.x) bb.max.x = p.x;
        if (bb.min.y > p.y) bb.min.y = p.y;
        if (bb.max.y < p.y) bb.max.y = p.y;
        sommet = sommet->next;
    }

    bb.min.x -= padding;
    bb.min.y -= padding;
    bb.max.x += padding;
    bb.max.y += padding;

    return bb;
}

char is_inside_polygone(Polygone poly, Point t1, Point t2) {
    struct _sommet * sommets = poly.sommets;
    Point p1 = sommets->point, p2;
    sommets = sommets->next;
    unsigned int nb_inter = 0;
    double d, d2, d3, d4;

    Point v, k;

    for (; sommets != poly.sommets; sommets = sommets->next) {
        p2 = sommets->point;

        v = (Point) { p2.x - p1.x, p2.y - p1.y };
        k = (Point) { t2.x - t1.x, t2.y - t2.x };

        d = v.x * (t1.y - p1.y) - v.y * (t1.x - p1.x);
        d2 = v.x * (t2.y - p1.y) - v.y * (t2.x - p1.x);
        d3 = k.x * (p2.y - t1.y) - k.y * (p2.x - t1.x);
        d4 = k.x * (p1.y - t1.y) - k.y * (p1.x - t1.x);

        if ((d > 0 && d2 < 0 && d3 > 0 && d4 < 0) ||
                (d < 0 && d2 > 0 && d3 > 0 && d4 < 0) ||
                (d > 0 && d2 < 0 && d3 < 0 && d4 > 0) ||
                (d < 0 && d2 > 0 && d3 < 0 && d4 > 0)) {
            nb_inter++;
        }

        p1 = p2;
    }

    return (nb_inter % 2) != 0;
}

void scan_line_fill(Polygone polygone) {
    if (!polygone.is_closed) return;

    glBegin(GL_POINTS);

    BoundingBox box = get_polygone_bounding_box(polygone);

    for (int y = box.min.y; y <= box.max.y; y++) {
        for (int x = box.min.x; x <= box.max.x; x++) {
            if (is_inside_polygone(polygone, (Point) { x, y }, box.max)) {
                glVertex2i(x, y);
            }
        }
    }

    glEnd();
}
