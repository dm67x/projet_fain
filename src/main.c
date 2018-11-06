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

Polygone polygone, currentNode;
int fill;

enum MODE {
    NONE,
    INSERT,
    VERTEX,
    EDGE
};

enum MODE current_mode = NONE;

void display_func() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);

    drawPolygon(polygone);

    if (current_mode == VERTEX && currentNode) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        Point p = currentNode->point;
        glVertex2i(p.x - 8, p.y - 8);
        glVertex2i(p.x + 8, p.y - 8);
        glVertex2i(p.x + 8, p.y + 8);
        glVertex2i(p.x - 8, p.y + 8);
        glEnd();
    } else if (current_mode == EDGE && currentNode) {
        glColor3f(1.0f, 0.0f, 0.0f);
        Point p = currentNode->point;
        if (currentNode->next) {
            Point p2 = currentNode->next->point;
            bresenham(p, p2);
        }
    }

    if (fill) {
        glColor3f(1.0f, 0.0f, 1.0f);
        //scan_line_fill(polygone);
    }

    glutSwapBuffers();
}

void keyboard_func(unsigned char key, int x, int y) {
    (void)x;
    (void)y;

    switch (key) {
    case 27:
        exit(0);

    case 'c':
        break;

    case 'f':
        fill = !fill;
        break;

    case 'i':
        current_mode = current_mode == INSERT ? NONE : INSERT;
		if (current_mode == INSERT) glutSetCursor(GLUT_CURSOR_CROSSHAIR);
		else glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        break;

    case 'v':
        current_mode = current_mode == VERTEX ? NONE : VERTEX;
        currentNode = polygone;
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        break;

    case 'e':
        current_mode = current_mode == EDGE ? NONE : EDGE;
        currentNode = polygone;
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
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
            nextPointFromPolygon(polygone, &currentNode);
            break;

        case GLUT_KEY_PAGE_DOWN:
            prevPointFromPolygon(polygone, &currentNode);
            break;

        case GLUT_KEY_END:
            polygone = deletePointFromPolygon(polygone, &currentNode);
            break;

        case GLUT_KEY_UP:
            p = currentNode->point;
            p.y--;
            currentNode->point = p;
            break;

        case GLUT_KEY_DOWN:
            p = currentNode->point;
            p.y++;
            currentNode->point = p;
            break;

        case GLUT_KEY_LEFT:
            p = currentNode->point;
            p.x--;
            currentNode->point = p;
            break;

        case GLUT_KEY_RIGHT:
            p = currentNode->point;
            p.x++;
            currentNode->point = p;
            break;
        }
        break;

    case EDGE:
        switch (key) {
        case GLUT_KEY_PAGE_UP:
            nextPointFromPolygon(polygone, &currentNode);
            break;

        case GLUT_KEY_PAGE_DOWN:
            prevPointFromPolygon(polygone, &currentNode);
            break;
        }
        break;
    }
    glutPostRedisplay();
}

void mouse_func(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && current_mode == INSERT) {
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
    currentNode = polygone;
    fill = 0;

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
