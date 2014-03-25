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
        if(strcmp(opcode, "label") == 0)
        {
            strcpy(instrTable.entry[address].opcode, "nop");
            store(&jumpTable, operand, address);
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

int sub(int pc)
{
    int rop = stackPop(&stack);
    int lop = stackPop(&stack);
    stackPush(&stack, lop - rop);
    return pc + 1;
}

int mul(int pc)
{
    int rop = stackPop(&stack);
    int lop = stackPop(&stack);
    stackPush(&stack, lop * rop);
    return pc + 1;
}

int divide(int pc)
{
    int rop = stackPop(&stack);
    int lop = stackPop(&stack);
    if(rop == 0)
    {
        printf("HEY NO DIVIDING BY A ZERO SILLY\n");
        printf("obviously halting execution...\n");
        exit(1);
    }
    stackPush(&stack, lop / rop);
    return pc + 1;
}

int get(int pc, char *operand)
{
    int val;
    int valid = -1;
    char numstring[20];

    while(valid < 0)
    {
        int i = 0;
        printf("Enter %s > ", operand);
        fgets(numstring, 20, stdin);
        if(numstring[0] == '-' || isdigit(numstring[0]))
        {
            if(numstring[0] == '-')
                i = 1;
            //make sure every char given is a digit
            for(i; i < strlen(numstring)-1; i++)
            {
                if(!isdigit(numstring[i]))
                {
                    printf("Error, please input a number\n");
                    valid = -1;
                    break;
                }
                else
                    valid = 1;
            }
        }
        else
        {
            printf("Error, please input a number\n");
            valid = -1;
        }
    }

    /**val = strtol(numstring, &endptr, 10);
    char * endptr;
    if(*endptr != '\n')
    {
        while(fgetc(stdin) != '\n')
        {

        }
    }*/

    val = atoi(numstring);
    store(&symbolTable, operand, val);
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

//logical not bitwise
int not(int pc)
{
    int op = stackPop(&stack);
    stackPush(&stack, !op); 
    return pc + 1;
}

//logical not bitwise
int and(int pc)
{
    int rop = stackPop(&stack);
    int lop = stackPop(&stack);
    stackPush(&stack, lop && rop);
    return pc + 1;
}

//logical not bitwise
int or(int pc)
{
    int rop = stackPop(&stack);
    int lop = stackPop(&stack);
    stackPush(&stack, lop || rop);
    return pc + 1;
}

int testeq(int pc)
{
    int op = stackPop(&stack);
    if(op == 0)
        stackPush(&stack, 1);
    else 
        stackPush(&stack, 0);
    return pc + 1;
}

int testne(int pc)
{
    int op = stackPop(&stack);
    if(op != 0)
        stackPush(&stack, 1);
    else
        stackPush(&stack, 0);
    return pc + 1;
}

int testlt(int pc)
{
    int op = stackPop(&stack);
    if(op < 0)
        stackPush(&stack, 1);
    else
        stackPush(&stack, 0);
    return pc + 1;
}

int testle(int pc)
{
    int op = stackPop(&stack);
    if(op <= 0)
        stackPush(&stack, 1);
    else
        stackPush(&stack, 0);
    return pc + 1;
}

int testgt(int pc)
{
    int op = stackPop(&stack);
    if(op > 0)
        stackPush(&stack, 1);
    else
        stackPush(&stack, 0);
    return pc + 1;
}

int testge(int pc)
{
    int op = stackPop(&stack);
    if(op >= 0)
        stackPush(&stack, 1);
    else
        stackPush(&stack, 0);
    return pc + 1;
}

//unconditional
int jump(int pc, char * operand)
{
    int newpc = retrieve(&jumpTable, operand);
    return newpc;
}

//conditional jump on false
int jf(int pc, char * operand)
{
    int val = stackPop(&stack);
    if(val == 1)
        return pc + 1;
    else
        return retrieve(&jumpTable, operand);
}

int halt(int pc)
{
    return pc + 1;
}
