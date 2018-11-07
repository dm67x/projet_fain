#if WIN32
#include <windows.h>
#endif

#include "polygon.h"
#include <stdlib.h>
#include "bresenham.h"
#include <GL/gl.h>
#include <stdio.h>
#include <math.h>

Polygone newPolygone() {
    Polygone poly;
    poly.nb_sommets = 0;
    poly.sommets = NULL;
    poly.is_closed = 0;
    poly.current = NULL;
    poly.last = NULL;
    return poly;
}

void insertAfter(struct _sommet * sommet, struct _sommet * newSommet) {
    newSommet->next = sommet->next;
    newSommet->prev = sommet;
    sommet->next->prev = newSommet;
    sommet->next = newSommet;
}

void addPointToPolygone(Polygone * poly, Point p) {
    if (!poly) return;
    if (poly->is_closed) return;

    struct _sommet * sommet = (struct _sommet *)malloc(sizeof(struct _sommet));
    sommet->point = p;

    if (!poly->last) {
        sommet->prev = sommet;
        sommet->next = sommet;
        poly->sommets = sommet;
    } else {
        insertAfter(poly->last, sommet);
    }
    poly->last = sommet;
    poly->nb_sommets += 1;
}

void removePointFromPolygone(Polygone * poly, struct _sommet * sommet) {
    if (!poly) return;
    if (!poly->current) return;

    if (sommet->next == sommet) {
        poly->last = NULL;
    } else {
        sommet->next->prev = sommet->prev;
        sommet->prev->next = sommet->next;
        if (sommet == poly->last)
            poly->last = sommet->prev;
    }

    poly->nb_sommets -= 1;

    if (sommet == poly->current)
        poly->current = poly->last;

    if (sommet == poly->sommets)
        poly->sommets = sommet->next;

    if (poly->nb_sommets == 0) {
        poly->sommets = NULL;
        poly->current = NULL;
    }

    if (poly->is_closed)
        poly->is_closed = 0;

    free(sommet);
}

void scinderArcInsidePolygone(Polygone * poly) {
    if (!poly) return;
    if (!poly->current) return;

    struct _sommet * new_sommet = (struct _sommet *)malloc(sizeof(struct _sommet));
    struct _sommet * courant = poly->current;
    struct _sommet * next = poly->current->next;

    Point a = courant->point;
    Point b = next->point;
    Point milieu = (Point) { (a.x + b.x) / 2, (a.y + b.y) / 2 };

    new_sommet->point = milieu;
    insertAfter(courant, new_sommet);
}

void nextPointInsidePolygone(Polygone * poly) {
    if (!poly->current) poly->current = poly->sommets;
    poly->current = poly->current->next;
}

void prevPointInsidePolygone(Polygone * poly) {
    if (!poly->current) poly->current = poly->sommets;
    poly->current = poly->current->prev;
}

void closePolygone(Polygone * poly) {
    addPointToPolygone(poly, poly->last->next->point);
    poly->is_closed = 1;
}

void openPolygone(Polygone * poly) {
    removePointFromPolygone(poly, poly->last);
}

void drawPolygone(Polygone poly) {
    if (!poly.sommets) return;

    struct _sommet * sommet = poly.sommets;
    Point p1 = sommet->point;

    if (sommet == sommet->next) {
        glBegin(GL_POINTS);
        glVertex2i(p1.x, p1.y);
        glEnd();
        return;
    }

    sommet = sommet->next;

    while (sommet != poly.sommets) {
        Point p2 = sommet->point;
        bresenham(p1, p2);
        p1 = p2;
        sommet = sommet->next;
    }
}
