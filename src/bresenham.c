#if WIN32
#include <windows.h>
#endif

#include "bresenham.h"
#include <GL/gl.h>
#include <math.h>

void Z2_to_1erOctant(Point from, Point to, Point * pA_1o, Point * pB_1o) {
    Point pA_1q, pB_1q;

    if (to.x > from.x) {
        pA_1q.x = from.x;
        pB_1q.x = to.x;
    } else {
        pA_1q.x = -from.x;
        pB_1q.x = -to.x;
    }

    if (to.y > from.y) {
        pA_1q.y = from.y;
        pB_1q.y = to.y;
    } else {
        pA_1q.y = -from.y;
        pB_1q.y = -to.y;
    }

    if (pB_1q.x - pA_1q.x > pB_1q.y - pA_1q.y) {
        *pA_1o = pA_1q;
        *pB_1o = pB_1q;
    } else {
        pA_1o->x = pA_1q.y;
        pA_1o->y = pA_1q.x;
        pB_1o->x = pB_1q.y;
        pB_1o->y = pB_1q.x;
    }
}

void O1_to_Z2(Point from, Point to, Point p_1o, Point * p) {
    Point p_1q;

    if (abs(to.x - from.x) > abs(to.y - from.y)) {
        p_1q = p_1o;
    } else {
        p_1q.x = p_1o.y;
        p_1q.y = p_1o.x;
    }

    if (to.x > from.x) {
        p->x = p_1q.x;
    } else {
        p->x = -p_1q.x;
    }

    if (to.y > from.y) {
        p->y = p_1q.y;
    } else {
        p->y = -p_1q.y;
    }
}

void bresenham(Point from, Point to) {
    Point p1, p2, p_Z2;

    Z2_to_1erOctant(from, to, &p1, &p2);
    double dx = p2.x - p1.x, dy = p2.y - p1.y;
    double incrd1 = 2 * dy, incrd2 = 2 * (dy - dx);
    double d = 2 * dy - dx;
    glBegin(GL_POINTS);
    while (p1.x < p2.x) {
        O1_to_Z2(from, to, p1, &p_Z2);
        glVertex2i(p_Z2.x, p_Z2.y);
        p1.x += 1;
        if (d < 0) {
            d += incrd1;
        } else {
            p1.y += 1;
            d += incrd2;
        }
    }
    O1_to_Z2(from, to, p1, &p_Z2);
    glVertex2i(p_Z2.x, p_Z2.y);
    glEnd();
}
