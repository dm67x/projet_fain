#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>

#define DEBUG 1

#include "polygon.h"

static Polygone * polygone;
static int fx, fy;
static int first;

void display_func() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);

    drawPolygon(polygone);

    glutSwapBuffers();
}

void keyboard_func(unsigned char key, int x, int y) {
    (void)x;
    (void)y;
    if (key == 27) {
        exit(0);
    } else if (key == 'c') {
        Point p = polygone->p;
        polygone = addPointToPolygon(polygone, (Point) { fx, fy });
        fx = p.x;
        fy = p.y;
    } else if (key == 'f') {

    }
    glutPostRedisplay();
}

void mouse_func(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        if (first) {
            first = 0;
            fx = x; fy = y;
        }
        polygone = addPointToPolygon(polygone, (Point){ x, y });
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

    polygone = newPolygon();
    first = 1;
    fx = fy = 0;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glOrtho(0, width, height, 0, -1, 1);
    glutDisplayFunc(display_func);
    glutKeyboardFunc(keyboard_func);
    glutMouseFunc(mouse_func);
    glutMainLoop();
    return 0;
}
