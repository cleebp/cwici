/**
 * teststack.c
 *
 * Modified from Dr. Fenwick's original file.
 *
 * This class tests the stack.c functionality of the wic 
 * interpreter.
 *
 * @author Brian Clee
 * @version 3/18/14
 */

#include <stdio.h>
#include "stack.h"

void simpleTest(stackType);

int main()
{
    //initialize
    stackType stack;
    printf("Initializing stack for testing\n\n");
    initializeStack(&stack);
    
    simpleTest(stack);

    printf("\n\nClearing stack for more tests\n\n");
    initializeStack(&stack);

    advancedTest(stack);

    return 0;
}

void simpleTest(stackType stack)
{
    printf("==================================\n");
    printf("== Beggining simple stack tests ==\n");
    printf("==================================\n");

    //push
    printf("Pushing: %d\n", 3);
    stackPush(&stack, 3);

    //pop and compare
    printf("Popping...");
    int x = stackPop(&stack);
    if (x == 3)
        printf("success\n");
    else
        printf("** ERROR **\n");

    //two pushes
    printf("Pushing: %d\n", 4);
    stackPush(&stack, 4);
    printf("Pushing: %d\n", 5);
    stackPush(&stack, 5);
    
    //pop and compare
    printf("Popping...");
    x = stackPop(&stack);
    if (x == 5)
        printf("success\n");
    else
        printf("** ERROR **\n");

    //two pushes
    printf("Pushing: %d\n", 6);
    stackPush(&stack, 6);
    printf("Pushing: %d\n", 7);
    stackPush(&stack, 7);

    //test stack print
    printf("Stack contents (should be 7,6,4):\n");
    printStack(&stack);
}
