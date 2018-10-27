#include <GL/glut.h>
#include <GL/gl.h>

#define WIDTH 800
#define HEIGHT 800

void display_func() {
    glClear(GL_COLOR_BUFFER_BIT);

    glutSwapBuffers();
}

int main(int argc, char ** argv) {
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInit(&argc, argv);
    glutCreateWindow("FAIN - Projet");

    glViewport(0, 0, WIDTH, HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
    glutDisplayFunc(display_func);
    glutMainLoop();
    return 0;
}
