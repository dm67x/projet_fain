#include "stack.h"
#include <stdlib.h>
#include "bresenham.h"

Stack * newStack() {
    return NULL;
}

Stack * pushStack(Stack * s, Point p) {
    Stack * n = (Stack *)malloc(sizeof(struct Stack));
    n->next = s;
    n->point = p;
    return n;
}

Stack * popStack(Stack * s) {
    Stack * n = s->next;
    free(s);
    return n;
}

Point topStack(Stack * s) {
    return s->point;
}

void drawStack(Stack * s) {
    if (s == NULL) return;
    Point p = topStack(s);
    s = s->next;

    while (s != NULL) {
        Point p2 = topStack(s);
        s = s->next;
        bresenham(p, p2);
        p = p2;
    }
}
