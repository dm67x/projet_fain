#if WIN32
#include <windows.h>
#endif

#include "scan_line_filling.h"
#include <stdlib.h>
#include <GL/gl.h>

void find_min_max(Polygone polygone, Point * min, Point * max) {
    if (!polygone.sommets) return;

    struct _sommet * sommet = polygone.sommets;

    *min = *max = sommet->point;
    sommet = sommet->next;

    while (sommet != polygone.sommets) {
        Point pt = sommet->point;
        if (min->x > pt.x) min->x = pt.x;
        if (max->x < pt.x) max->x = pt.x;
        if (min->y > pt.y) min->y = pt.y;
        if (max->y < pt.y) max->y = pt.y;
        sommet = sommet->next;
    }
}

void find_intersections(Polygone polygone, Point * intersections) {
    Point min, max;
    find_min_max(polygone, &min, &max);

    for (int y = min.y; y <= max.y; y++) {

    }
}

void scan_line_fill(Polygone polygone) {
    Point min, max;

    glBegin(GL_LINES);

    find_min_max(polygone, &min, &max);
    for (int y = min.y; y <= max.y; y += 2) {
        glVertex2i(min.x, y);
        glVertex2i(max.x, y);
    }

    glEnd();
}
