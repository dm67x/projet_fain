#if WIN32
#include <windows.h>
#endif

#include "polygon.h"
#include <stdlib.h>
#include "bresenham.h"
#include <GL/gl.h>
#include <stdio.h>

Polygone newPolygon() {
    return NULL;
}

Polygone addPointToPolygon(Polygone poly, Point p) {
    Polygone npoly = (Polygone)malloc(sizeof(struct _polygone));
    npoly->point = p;
    npoly->prev = NULL;

    if (!poly) {
        npoly->next = NULL;
    } else {
        npoly->next = poly;
        poly->prev = npoly;
    }

    return npoly;
}

Polygone deletePointFromPolygon(Polygone poly, Polygone * current) {
    if (!poly) return poly;
    if (!(*current)) return poly;

    Polygone next = (*current)->next;
    Polygone prev = (*current)->prev;

    if (!next && !prev) {
        free((*current));
        *current = NULL;
        return NULL;
    }

    if (prev && !next) {
        prev->next = NULL;
        free(current);
        *current = prev;
        return poly;
    }

    if (!prev && next) {
        next->prev = NULL;
        free(current);
        *current = next;
        return next;
    }

    prev->next = next;
    next->prev = prev;
    free((*current));
    *current = next;
    return poly;
}

void nextPointFromPolygon(Polygone poly, Polygone * current) {
    if (!poly) return;
    if (!(*current)) return;
    *current = (*current)->next ? (*current)->next : (*current);
}

void prevPointFromPolygon(Polygone poly, Polygone * current) {
    if (!poly) return;
    *current = (*current)->prev ? (*current)->prev : (*current);
}

void drawPolygon(Polygone poly) {
    if (!poly) return;
    Point p = poly->point, p2;

    if (!poly->next) {
        glBegin(GL_POINTS);
        glVertex2i(p.x, p.y);
        glEnd();
        return;
    }

    poly = poly->next;
    for (; poly; poly = poly->next) {
        p2 = poly->point;
        bresenham(p, p2);
        p = p2;
    }
}
