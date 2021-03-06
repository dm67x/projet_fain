#if WIN32
#include <windows.h>
#endif

#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>

#include "bresenham.h"
#include "polygon.h"
#include "scan_line_filling.h"

static Polygone polygone;
static char fill;

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

    draw_polygone(polygone);

    if (current_mode == VERTEX && polygone.current) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        Point p = polygone.current->point;
        glVertex2i(p.x - 8, p.y - 8);
        glVertex2i(p.x + 8, p.y - 8);
        glVertex2i(p.x + 8, p.y + 8);
        glVertex2i(p.x - 8, p.y + 8);
        glEnd();
    } else if (current_mode == EDGE && polygone.current) {
        glColor3f(1.0f, 0.0f, 0.0f);
        Point p = polygone.current->point;
        Point p2 = polygone.current->next->point;
        bresenham(p, p2);
    }

    if (fill) {
        scan_line_fill(polygone);
    }

    glutSwapBuffers();
}

void keyboard_func(unsigned char key, int x, int y) {
    (void)x;
    (void)y;

    switch (key) {
    case 27:
        exit(0);

	case 127:
		if (current_mode == VERTEX) 
			remove_point_from_polygone(&polygone, polygone.current);
		break;

    case 'c':
        if (polygone.is_closed)
            open_polygone(&polygone);
        else
            close_polygone(&polygone);
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
        polygone.current = polygone.sommets;
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        break;

    case 'e':
        if (polygone.nb_sommets < 2) return;
        current_mode = current_mode == EDGE ? NONE : EDGE;
        polygone.current = polygone.sommets;
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
            next_point_inside_polygone(&polygone);
            break;

        case GLUT_KEY_PAGE_DOWN:
            prev_point_inside_polygone(&polygone);
            break;

        case GLUT_KEY_UP:
            p = polygone.current->point;
            p.y--;
            polygone.current->point = p;
            break;

        case GLUT_KEY_DOWN:
            p = polygone.current->point;
            p.y++;
            polygone.current->point = p;
            break;

        case GLUT_KEY_LEFT:
            p = polygone.current->point;
            p.x--;
            polygone.current->point = p;
            break;

        case GLUT_KEY_RIGHT:
            p = polygone.current->point;
            p.x++;
            polygone.current->point = p;
            break;
        }
        break;

    case EDGE:
        switch (key) {
        case GLUT_KEY_PAGE_UP:
            next_point_inside_polygone(&polygone);
            break;

        case GLUT_KEY_PAGE_DOWN:
            prev_point_inside_polygone(&polygone);
            break;
        }
        break;
    }
    glutPostRedisplay();
}

void mouse_func(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && current_mode == INSERT) {
        add_point_to_polygone(&polygone, (Point){ x, y });
    } 
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP && current_mode == EDGE) {
        scinder_arc_inside_polygone(&polygone);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && current_mode == VERTEX) {
		struct _sommet * sommet = closest_vertex_from_polygone(&polygone, (Point) { x, y });
		if (sommet)
			polygone.current = sommet;
	}
    glutPostRedisplay();
}

int main(int argc, char ** argv) {
    int width = 800, height = 800;
    if (argc > 3) {
        fprintf(stderr, "Usage: %s [width] [height]\n", argv[0]);
        return EXIT_FAILURE;
    } else {
        if (argc == 2) {
            width = height = atoi(argv[1]);
        } else if (argc == 3) {
            width = atoi(argv[1]);
            height = atoi(argv[2]);
        }
    }

    glutInitWindowSize(width, height);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInit(&argc, argv);
    glutCreateWindow("FAIN - Projet");

    polygone = new_polygone();
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
