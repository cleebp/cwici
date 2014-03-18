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
void advancedTest(stackType);

int main()
{
    //initialize
    stackType stack1;
    stackType stack2;
    printf("Initializing stack for testing\n\n");
    initializeStack(&stack1);
    initializeStack(&stack2);

    simpleTest(stack1);
    advancedTest(stack2);

    return 0;
}

void simpleTest(stackType stack)
{
    printf("==================================\n");
    printf("== Beginning simple stack tests ==\n");
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

void advancedTest(stackType stack)
{
    printf("\n====================================\n");
    printf("== Beginning advanced stack tests ==\n");
    printf("====================================\n");

    int i;
    //push full stack
    printf("Pushing numbers 0-19:\n");
    for(i = 0; i < STACK_SIZE; i++)
    {
        printf("pushing %d...\n", i);
        stackPush(&stack, i);
    }
    //pop and compare full stack
    printf("\nPopping 20 items:\n");
    int x = 0;
    for(i = 19; i >= 0; i--)
    {
        x = stackPop(&stack);
        printf("popping item %d...", i);
        if (x == i)
            printf("success\n", i);
        else
            printf("** ERROR **\n");
    }
}

