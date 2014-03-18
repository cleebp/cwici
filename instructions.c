#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "instructions.h"
#include "table.h"
#include "stack.h"

#define INSTR_TABLE_SIZE 100

typedef struct {
} instructionType;

typedef struct
{
} instructionTable;

// These 4 are "private" making them only accessible via public function
static instructionTable instrTable;
static tableType symbolTable;   //for variables and values
static tableType jumpTable;     //for labels
static stackType stack;         //for stack operations 

// This one is public so main can use it.
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

int fetchInstruction(int address, char * opcode, char * operand)
{
    return 1;
}

void insertInstruction(int address, char * opcode, char * operand)
{
}

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

//**********************************************************************
// Begin opcode function section.
//**********************************************************************
//Functions for various instructions go here. 
int nop(int pc) { return pc + 1; }

int add(int pc){
    int rop = stackPop(&stack);
    int lop = stackPop(&stack);
    stackPush(&stack, lop + rop + 1);
    return pc + 1;
}


