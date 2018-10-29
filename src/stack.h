#ifndef STACK_H
#define STACK_H

#include "point.h"

typedef struct Stack {
    struct Stack * next;
    Point point;
} Stack;

Stack * newStack();
Stack * pushStack(Stack * s, Point p);
Stack * popStack(Stack * s);
Point topStack(Stack * s);
void drawStack(Stack * s);

#endif // STACK_H
