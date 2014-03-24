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

void printInstrTable()
{
    int i;
    for(i = 0; i < instrTable.instructionCount; i++)
    {
        if(strcmp(instrTable.entry[i].opcode, "label") == 0)
        {
            printf("%s %s\n", instrTable.entry[i].operand,
                instrTable.entry[i].opcode);
        }
        else
        {
            printf("%s %s\n", instrTable.entry[i].opcode, 
                instrTable.entry[i].operand);
        }
    }
}

/**
 * Print all tables and stacks
 */
void printAll()
{
    printf("\n-----------------------\n");
    printf("-- Instruction Table --\n");
    printInstrTable();
    
    printf("\n------------------\n");
    printf("-- Symbol Table --\n");
    printTable(&symbolTable);
    
    printf("\n----------------\n");
    printf("-- Jump Table --\n");
    printTable(&jumpTable);
    
    printf("\n-----------\n");
    printf("-- Stack --\n");
    printStack(&stack);
}

/**
 * Given an address in the instrTable, take the opcode and operand at 
 * that address and store it into the opcode and operand pointers given.
 */
int fetchInstruction(int address, char * opcode, char * operand)
{
    if(address <= instrTable.instructionCount)
    {
        memcpy(opcode, instrTable.entry[address].opcode, OPCODE_SIZE+1);
        memcpy(operand, instrTable.entry[address].operand, OPERAND_SIZE+1);
    }
    else
    {
        printf("Invalid address fetched '%d', halting execution...\n", address);
        exit(2);
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
        if(strcmp(operand, "label") == 0)
        {
            strcpy(instrTable.entry[address].opcode, "nop");
            store(&jumpTable, opcode, address);
        }
        else
        {
            strcpy(instrTable.entry[address].opcode, opcode);
            strcpy(instrTable.entry[address].operand, operand);
        }    
        instrTable.instructionCount++;
    }
    else
    {
        printf("Invalid addres inserted '%d', halting execution...\n", address);
        exit(2);
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

//Functions for instructions 
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

//@TODO implement...
int sub(int pc)
{
    return pc + 1;
}

//@TODO implement...
int mul(int pc)
{
    return pc + 1;
}

//@TODO implement...
int divide(int pc)
{
    return pc + 1;
}

//@TODO Figure rest out, see page 76 in text
int get(int pc, char *operand)
{
    //grab int value from user, store into key (operand) value(given)
    
    //fgets reads input
    //strtol converts to int but can find errors easier than atoi
    
    int val;
    char numstring[10];
    char * endptr;
    

    val = strtol(numstring, &endptr, 10);
    if(*endptr != '\n')
    {
        printf("Some characters in string are not base 10 digits.");
    }
    return pc + 1;
}

int put(int pc, char *operand)
{
    //operand is key of symbol table
    int val = retrieve(&symbolTable, operand);
    printf("%d\n", val);
    return pc + 1;
}

int push(int pc, char * operand)
{
    int val;
    //get digit
    if(isdigit(operand[0]) || isdigit(operand[1]))
    {
        val = atoi(operand);
    }
    //get var
    else
    {
        val = retrieve(&symbolTable, operand);
    }
    //push val
    stackPush(&stack, val);
    return pc + 1;
}

int pop(int pc, char * operand)
{
    int var = stackPop(&stack);
    store(&symbolTable, operand, var);
    return pc + 1;
}

//@TODO implement...
int not(int pc)
{
    return pc + 1;
}

//@TODO implement...
int and(int pc)
{
    return pc + 1;
}

//@TODO implement...
int or(int pc)
{
    return pc + 1;
}

//@TODO implement...
int testeq(int pc)
{
    return pc + 1;
}

//@TODO implement...
int testne(int pc)
{
    return pc + 1;
}

//@TODO implement...
int testlt(int pc)
{
    return pc + 1;
}

//@TODO implement...
int testle(int pc)
{
    return pc + 1;
}

//@TODO implement...
int testgt(int pc)
{
    return pc + 1;
}

//@TODO implement...
int testge(int pc)
{
    return pc + 1;
}

//@TODO implement...
int jump(int pc, char * operand)
{
    return pc + 1;
}

//@TODO implement...
int jf(int pc, char * operand)
{
    return pc + 1;
}

int halt(int pc)
{
    return pc + 1;
}
