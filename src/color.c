#include "color.h"

Color get_pixel_color(Point p) {
    Color c;
    glReadPixels(p.x, p.y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &c);
    return c;
}
