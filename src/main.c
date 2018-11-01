#if WIN32
#include <windows.h>
#endif

#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>

#define DEBUG 1

#include "bresenham.h"
#include "polygon.h"
#include "scan_line_filling.h"

static Polygone * polygone;
static int fx, fy;
static int first;
static int fill;
static int selectedPoint;
static int nb_points;

enum MODE {
    NONE,
    INSERT,
    VERTEX,
    EDGE
};

static enum MODE current_mode = NONE;

void display_func() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);

    drawPolygon(polygone);

    if (selectedPoint >= 0 && current_mode == VERTEX) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        Point p = getPointFromPolygon(polygone, selectedPoint);
        glVertex2i(p.x - 8, p.y - 8);
        glVertex2i(p.x + 8, p.y - 8);
        glVertex2i(p.x + 8, p.y + 8);
        glVertex2i(p.x - 8, p.y + 8);
        glEnd();
    } else if (selectedPoint >= 0 && current_mode == EDGE) {
        glColor3f(1.0f, 0.0f, 0.0f);
        Point p = getPointFromPolygon(polygone, selectedPoint);
        if (selectedPoint + 1 < sizePolygon(polygone)) {
            Point p2 = getPointFromPolygon(polygone, selectedPoint + 1);
            bresenham(p, p2);
        }
    }

    if (fill) {
        glColor3f(1.0f, 0.0f, 1.0f);
        scan_line_fill(polygone);
    }

    glutSwapBuffers();
}

void keyboard_func(unsigned char key, int x, int y) {
    (void)x;
    (void)y;
    Point p;

    switch (key) {
    case 27:
        exit(0);

    case 'c':
        p = polygone->p;
        polygone = addPointToPolygon(polygone, nb_points, (Point) { fx, fy });
        nb_points++;
        fx = p.x;
        fy = p.y;
        break;

    case 'f':
        fill = !fill;
        break;

    case 'i':
        current_mode = current_mode == INSERT ? NONE : INSERT;
        break;

    case 'v':
        selectedPoint = 0;
        current_mode = current_mode == VERTEX ? NONE : VERTEX;
        break;

    case 'e':
        selectedPoint = 0;
        current_mode = current_mode == EDGE ? NONE : EDGE;
        break;
    }
    glutPostRedisplay();
}

void special_func(int key, int x, int y) {
    Point p;

    switch (current_mode) {
    case VERTEX:
        switch (key) {
        case GLUT_KEY_PAGE_UP:
            selectedPoint = (selectedPoint + 1) % sizePolygon(polygone);
            break;

        case GLUT_KEY_PAGE_DOWN:
            selectedPoint = abs((selectedPoint - 1) % sizePolygon(polygone));
            break;

        case GLUT_KEY_END:
            if (selectedPoint < 0) return;
            polygone = deletePointFromPolygon(polygone, selectedPoint);
            int size_poly = sizePolygon(polygone);
            selectedPoint = size_poly > 0 ? abs((selectedPoint - 1) % size_poly) : -1;
            nb_points--;
            break;

        case GLUT_KEY_UP:
            if (selectedPoint < 0) return;
            p = getPointFromPolygon(polygone, selectedPoint);
            p.y--;
            updatePointFromPolygone(polygone, selectedPoint, p);
            break;

        case GLUT_KEY_DOWN:
            if (selectedPoint < 0) return;
            p = getPointFromPolygon(polygone, selectedPoint);
            p.y++;
            updatePointFromPolygone(polygone, selectedPoint, p);
            break;

        case GLUT_KEY_LEFT:
            if (selectedPoint < 0) return;
            p = getPointFromPolygon(polygone, selectedPoint);
            p.x--;
            updatePointFromPolygone(polygone, selectedPoint, p);
            break;

        case GLUT_KEY_RIGHT:
            if (selectedPoint < 0) return;
            p = getPointFromPolygon(polygone, selectedPoint);
            p.x++;
            updatePointFromPolygone(polygone, selectedPoint, p);
            break;
        }
        break;

    case EDGE:
        switch (key) {
        case GLUT_KEY_PAGE_UP:
            selectedPoint = (selectedPoint + 1) % sizePolygon(polygone);
            break;

        case GLUT_KEY_PAGE_DOWN:
            selectedPoint = abs((selectedPoint - 1) % sizePolygon(polygone));
            break;
        }
        break;
    }
    glutPostRedisplay();
}

void mouse_func(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && current_mode == INSERT) {
        if (first || sizePolygon(polygone) == 0) {
            first = 0;
            fx = x; fy = y;
        }
        polygone = addPointToPolygon(polygone, nb_points, (Point){ x, y });
        nb_points++;
    }
    glutPostRedisplay();
}

int main(int argc, char ** argv) {
    int width = 800, height = 800;
#ifndef DEBUG
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s width [height]\n", argv[0]);
        return EXIT_FAILURE;
    } else {
        if (argc == 2) {
            width = height = atoi(argv[1]);
        } else {
            width = atoi(argv[1]);
            height = atoi(argv[2]);
        }
    }
#endif

    glutInitWindowSize(width, height);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInit(&argc, argv);
    glutCreateWindow("FAIN - Projet");
    glutSetCursor(GLUT_CURSOR_CROSSHAIR);

    polygone = newPolygon();
    first = 1;
    fx = fy = 0;
    fill = 0;
    selectedPoint = -1;
    nb_points = 0;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glOrtho(0, width, height, 0, -1, 1);
    glutDisplayFunc(display_func);
    glutKeyboardFunc(keyboard_func);
    glutSpecialFunc(special_func);
    glutMouseFunc(mouse_func);
    glutMainLoop();
    return 0;
}
