#ifndef COLOR_H
#define COLOR_H

#include <GL/gl.h>

typedef struct {
    GLfloat r;
    GLfloat g;
    GLfloat b;
} Color;

Color getPixelColor(GLint x, GLint y);

#endif // COLOR_H
