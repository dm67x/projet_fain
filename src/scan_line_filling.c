#if WIN32
#include <windows.h>
#endif

#include "scan_line_filling.h"
#include <stdlib.h>
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>

// Récupérer la bounding box (le fond)
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

// verifier si les droites s'intersectent
// pour cela je regarder les determinants des vecteurs i, j, v, w, z et -w
// si leurs déterminants s'opposent + et - alors intersection
char have_intersection(Point p1, Point p2, Point p3, Point p4) {
	double alpha, beta, gamma, epsilon;
	// vecteurs
	Point i, j, v, w, z;
	i = (Point) { p2.x - p1.x, p2.y - p1.y };
	j = (Point) { p4.x - p3.x, p4.y - p3.y };
	v = (Point) { p3.x - p2.x, p3.y - p2.y };
	w = (Point) { p4.x - p2.x, p4.y - p2.y };
	z = (Point) { p1.x - p4.x, p1.y - p4.y };

	alpha = i.y * v.x - i.x * v.y;
	beta = i.y * w.x - i.x * w.y;
	gamma = j.y * -w.x - j.x * -w.y;
	epsilon = j.y * z.x - j.x * z.y;

	if (alpha > 0 && beta < 0 && gamma > 0 && epsilon < 0) return 1;
	if (alpha > 0 && beta < 0 && gamma < 0 && epsilon > 0) return 1;
	if (alpha < 0 && beta > 0 && gamma > 0 && epsilon < 0) return 1;
	if (alpha < 0 && beta > 0 && gamma < 0 && epsilon > 0) return 1;
	return 0;
}

// Verification si le point est à l'intérieur du polygone
// Pour cela on verifie le nombre d'intersection de la droite partant du point t1 vers t2
// Si le résultat est impair alors le point t1 est dans le polygone sinon le point est à l'extérieur du polygone
char is_inside_polygone(Polygone poly, Point t1, Point t2) {
	if (!poly.is_closed) return 0;

    struct _sommet * sommets = poly.sommets;
    Point p1 = sommets->point, p2;
    sommets = sommets->next;
    unsigned int nb_inter = 0;
    double d, d2, d3, d4;

    Point v, k;

    for (; sommets != poly.sommets; sommets = sommets->next) {
        p2 = sommets->point;
		if (have_intersection(t1, t2, p1, p2)) nb_inter++;
        p1 = p2;
    }

	p2 = sommets->point;
	if (have_intersection(t1, t2, p1, p2)) nb_inter++;

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
