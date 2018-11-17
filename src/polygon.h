#ifndef POLYGON_H
#define POLYGON_H

#include "point.h"

#define SEARCH_PADDING 20

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

Polygone new_polygone();
void add_point_to_polygone(Polygone * poly, Point p);
void remove_point_from_polygone(Polygone * poly, struct _sommet * sommet);
void draw_polygone(Polygone poly);
void scinder_arc_inside_polygone(Polygone * poly);
void next_point_inside_polygone(Polygone * poly);
void prev_point_inside_polygone(Polygone * poly);
void close_polygone(Polygone * poly);
void open_polygone(Polygone * poly);
struct _sommet * closest_vertex_from_polygone(Polygone * poly, Point p);

#endif // POLYGON_H
