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
#define OPCODE_SIZE 6
#define OPERAND_SIZE 20

//instruction entries
typedef struct 
{
    char opcode[OPCODE_SIZE];
    char operand[OPERAND_SIZE];
} instructionType;

//table for instructions
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

/**
 * Given an address in the instrTable, take the opcode and operand at 
 * that address and store it into the opcode and operand pointers given.
 */
int fetchInstruction(int address, char * opcode, char * operand)
{
    if(address <= instrTable.instructionCount)
    {
        memcpy(opcode, instrTable.entry[address].opcode, OPCODE_SIZE);
        memcpy(operand, instrTable.entry[address].operand, OPERAND_SIZE);
    }
    else
    {
        printf("Invalid address fetched '%d', halting execution...\n", address);
        quit(1);
    }
    return 1;
}

/**
 * Takes an address and opcode/operand and stores the instruction
 * in the instrTable at that address. If the instr is a label then
 * a nop is inserted instead and an entry for the label name and given
 * address is stored in the jump table.
 */
void insertInstruction(int address, char * opcode, char * operand)
{
    if(address <= instrTable.instructionCount)
    {
        if(strcmp(*operand, @"label") == 0)
        {
            instrTable.entry[address].opcode = @"nop";
            store(&jumpTable, *opcode, address);
        }
        else
        {
            instrTable.entry[address].opcode = *opcode;
            instrTable.entry[address].operand = *operand;
        }    
        instrTable.instructionCount++;
    }
    else
    {
        printf("Invalid addres inserted '%d', halting execution...\n", address);
        quit(1);
    }
}

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

    else { return 1; } //label
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
