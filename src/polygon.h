#ifndef POLYGON_H
#define POLYGON_H

#include "point.h"

struct _sommet {
    struct _sommet * next;
    struct _sommet * prev;
    Point point;
};

struct _polygone {
    struct _sommet * sommets;
    struct _sommet * last; // dernier sommet
    struct _sommet * current; // sommet courant selectionné
    int nb_sommets; // nombre de sommets réels
    char is_closed; // si polygone fermé
};

typedef struct _polygone Polygone;

Polygone newPolygone();
void addPointToPolygone(Polygone * poly, Point p);
void removePointFromPolygone(Polygone * poly, struct _sommet * sommet);
void drawPolygone(Polygone poly);
void scinderArcInsidePolygone(Polygone * poly);
void nextPointInsidePolygone(Polygone * poly);
void prevPointInsidePolygone(Polygone * poly);
void closePolygone(Polygone * poly);
void openPolygone(Polygone * poly);

#endif // POLYGON_H
