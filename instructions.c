/**
 * instructions.c
 *
 * Modified with permission from Dr. Fenwick.
 *
 * This class implements the instruction data structures,
 * but not the execution functions.
 *
 * @author Brian Clee
 * @version 3/19/14
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instructions.h"
#include "table.h"
#include "stack.h"

#define INSTR_TABLE_SIZE 100
#define OP_SIZE 20

//@TODO
typedef struct 
{
    char opcode[OP_SIZE];
    char operand[OP_SIZE];
} instructionType;

//@TODO
typedef struct
{
    int instructionCount;
    instructionType entry[INSTR_TABLE_SIZE]; 
} instructionTable;

static instructionTable instrTable;
static tableType symbolTable;   //for variables and values
static tableType jumpTable;     //for labels
static stackType stack;         //for stack operations 

//called by main yo
void initialize()
{
    instrTable.instructionCount = 0; 
    initializeTable(&symbolTable);
    initializeTable(&jumpTable);
    initializeStack(&stack);
}

void printSymbolTable()
{
    printTable(&symbolTable);
}

//@TODO
int fetchInstruction(int address, char * opcode, char * operand)
{
    return 1;
}

//@TODO
void insertInstruction(int address, char * opcode, char * operand)
{

}

//this needs to be reformated...
//perhaps all opcodes can be constant ints then just switch
//@TODO fix this mess...
int hasOperand(char * opcode)
{
    if(strcmp(opcode, "get") == 0){return 1;}
    else if(strcmp(opcode, "put") == 0){return 1;}
    else if(strcmp(opcode, "push") == 0){return 1;}
    else if(strcmp(opcode, "pop") == 0){return 1;}
    else if(strcmp(opcode, "j") == 0){return 1;}
    else if(strcmp(opcode, "jf") == 0){return 1;}

    else if (strcmp(opcode, "nop") == 0){return 0;}
    else if (strcmp(opcode, "add") == 0){return 0;}
    else if (strcmp(opcode, "sub") == 0){return 0;}
    else if (strcmp(opcode, "mul") == 0){return 0;}
    else if (strcmp(opcode, "div") == 0){return 0;}
    else if (strcmp(opcode, "and") == 0){return 0;}
    else if (strcmp(opcode, "not") == 0){return 0;}
    else if (strcmp(opcode, "or") == 0){return 0;}
    else if (strcmp(opcode, "tsteq") == 0){return 0;}
    else if (strcmp(opcode, "tstne") == 0){return 0;}
    else if (strcmp(opcode, "tstlt") == 0){return 0;}
    else if (strcmp(opcode, "tstle") == 0){return 0;}
    else if (strcmp(opcode, "tstgt") == 0){return 0;}
    else if (strcmp(opcode, "tstge") == 0){return 0;}
    else if (strcmp(opcode, "halt") == 0){return 0;}

    else { return 1; } // must be a label!!
}

//Functions for various instructions go here. 
int nop(int pc) 
{ 
    return pc + 1; 
}

int add(int pc)
{
    int rop = stackPop(&stack);
    int lop = stackPop(&stack);
    stackPush(&stack, lop + rop);
    return pc + 1;
}

//@TODO implement all remainign instructions...
