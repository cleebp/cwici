/**
 * stack.h
 *
 * Modified with permission from code written by Dr. Fenwick.
 *
 * @author Brian Clee
 * @version 3/18/14
 */

#ifndef STACK_H_
#define STACK_H_

#define STACK_SIZE 20 //maximum stack size

typedef struct
{
	int top;
	int items[STACK_SIZE];
} stackType;

//function prototypes
void initializeStack(stackType * s);
void stackPush(stackType *, int x);
int stackPop(stackType *);
void printStack(stackType *);

#endif
