#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>

#include "stack.h"

static Stack * pointsStack;
static int fx, fy;
static int first;

void display_func() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);

    drawStack(pointsStack);

    glutSwapBuffers();
}

void keyboard_func(unsigned char key, int x, int y) {
    (void)x;
    (void)y;
    if (key == 27) {
        exit(0);
    } else if (key == 99) {
        Point p = topStack(pointsStack);
        pointsStack = pushStack(pointsStack, (Point) { fx, fy });
        fx = p.x;
        fy = p.y;
    }
    glutPostRedisplay();
}

void mouse_func(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        printf("%d %d\n", x, y);
        if (first) {
            first = 0;
            fx = x; fy = y;
        }
        pointsStack = pushStack(pointsStack, (Point){ x, y });
    }
    glutPostRedisplay();
}

int main(int argc, char ** argv) {
    int width = 800, height = 800;
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

    glutInitWindowSize(width, height);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInit(&argc, argv);
    glutCreateWindow("FAIN - Projet");

    pointsStack = newStack();
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
