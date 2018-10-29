#include "polygon.h"
#include <stdlib.h>
#include "bresenham.h"
#include <GL/gl.h>
#include <stdio.h>

Polygone * newPolygon() {
    return NULL;
}

Polygone * addPointToPolygon(Polygone * p, int index, Point pt) {
    Polygone * n = (Polygone *)malloc(sizeof(struct PolygonePoint));
    n->p = pt;

    if (p == NULL) {
        n->next = NULL;
        n->prev = NULL;
        return n;
    }

    if (sizePolygon(p) < index) return p;

    if (index == 0) {
        n->next = p;
        n->prev = NULL;
        p->prev = n;
        return n;
    }

    Polygone * tmp = p;
    int i = 1;
    while (tmp != NULL) {
        if (i == index) {
            n->next = tmp->next;
            n->prev = tmp;
            tmp->next = n;
            break;
        }
        i++;
    }

    return p;
}

Point getPointFromPolygon(Polygone * p, int index) {
    for(int i = 0; p != NULL; p = p->next, i++) {
        if (i == index) {
            return p->p;
        }
    }
    return (Point) { -1, -1 };
}

Polygone * replacePointFromPolygon(Polygone * p, int index, Point pt) {
    p = deletePointFromPolygon(p, index);
    p = addPointToPolygon(p, index, pt);
    return p;
}

Polygone * deletePointFromPolygon(Polygone * p, int index) {
    if (p == NULL) return NULL;
    if (sizePolygon(p) < index) return p;

    if (index == 0) {
        Polygone * n = p->next;
        n->prev = NULL;
        free(p);
        return n;
    }

    Polygone * tmp = p->next;
    int i = 1;
    while (tmp != NULL) {
        if (i == index) {
            Polygone * prev = tmp->prev;
            Polygone * next = tmp->next;
            free(tmp);
            prev->next = next;
            next->prev = prev;
            break;
        }
        i++;
        tmp = tmp->next;
    }
    return p;
}

int sizePolygon(Polygone * p) {
    if (p == NULL) return 0;
    int i;
    for (i = 0; p != NULL; p = p->next, i++);
    return i;
}

void drawPolygon(Polygone * p) {
    if (p == NULL) return;
    if (sizePolygon(p) == 1) {
        glBegin(GL_POINTS);
        glVertex2i(p->p.x, p->p.y);
        glEnd();
        return;
    }

    Point p1 = p->p;
    p = p->next;

    for (; p != NULL; p = p->next) {
        Point p2 = p->p;
        bresenham(p1, p2);
        p1 = p2;
    }
}
