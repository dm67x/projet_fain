#ifndef COLOR_H
#define COLOR_H

#include <GL/gl.h>
#include "point.h"

typedef struct {
    GLubyte r;
    GLubyte g;
    GLubyte b;
} Color;

Color get_pixel_color(Point p);

#endif // COLOR_H
