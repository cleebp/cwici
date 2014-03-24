/**
 * main.c
 *
 * Modified with permission from Dr. Fenwick.
 *
 * Obviously main is the major control flow and designator.
 * Right now main can read wic instructions.
 *
 * @author Brian Clee
 * @version 3/19/14
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdarg.h>
#include "instructions.h"

static void readInstructions(FILE * fp);
static void discardline(FILE * fp);
static void execute();

int main(int argc, char * argv[])
{
    //First things first. Open the input file.
    FILE *fp;
    int i = 0;
    
    if (argc != 2 || (fp = fopen(argv[1], "r")) == NULL) 
    {
        printf("File open failed.\nUsage: %s <input file>\n",argv[0]);
        exit(1);
    }

    //initialize the symbol table, jump table and stack to 0
    initialize();

    //read the input file and prepare structures
    readInstructions(fp);
    fclose(fp); 

    //begin to interpret
    execute();

    printf("\nProgram halted\n");
}

void readInstructions(FILE * fp)
{
    int address = 0;
    char opcode[OPCODE_SIZE];
    char operand[OPERAND_SIZE];

    //infinite loop fetch until fscanf returns EOF or -1
    while(fscanf(fp, "%s", opcode) != EOF)
    {
        //check if opcode expects an operand and read if it does
        if(hasOperand(opcode))
        {
            fscanf(fp, "%s", operand);

            if(!strcmp(operand, "label"))
            {
                //flip opcode and operand if label
                strcpy(operand, opcode);
                strcpy(opcode, "label");
            }
        }
        else
        {
            strcpy(operand, "");
        }

        //insert aqcuired opcode/operand at address and incr address
        insertInstruction(address, opcode, operand);
        address++;

        //discard rest of the current line in case of comments
        discardline(fp);
    }
}

void execute()
{
    //part 3 required this
    printInstrTable();    

    //regular execution
    int pc = 0;
    char opcode[OPCODE_SIZE];
    char operand[OPERAND_SIZE];
    //fetchInstruction(pc, opcode, operand);
    while(strcmp(opcode, "halt"))
    {
        fetchInstruction(pc, opcode, operand);
        //execute that instruction
        //please excuse my dear awful code
        if(strcmp(opcode, "get") == 0){pc = get(pc, operand);}
        else if(strcmp(opcode, "put") == 0){pc = put(pc, operand);}
        else if(strcmp(opcode, "push") == 0){pc = push(pc, operand);}
        else if(strcmp(opcode, "pop") == 0){pc = pop(pc, operand);}
        else if(strcmp(opcode, "j") == 0){pc = jump(pc, operand);}
        else if(strcmp(opcode, "jf") == 0){pc = jf(pc, operand);}
        else if (strcmp(opcode, "nop") == 0){pc = nop(pc);}
        else if (strcmp(opcode, "add") == 0){pc = add(pc);}
        else if (strcmp(opcode, "sub") == 0){pc = sub(pc);}
        else if (strcmp(opcode, "mul") == 0){pc = mul(pc);}
        else if (strcmp(opcode, "div") == 0){pc = divide(pc);}
        else if (strcmp(opcode, "and") == 0){pc = and(pc);}
        else if (strcmp(opcode, "not") == 0){pc = not(pc);}
        else if (strcmp(opcode, "or") == 0){pc = or(pc);}
        else if (strcmp(opcode, "tsteq") == 0){pc = testeq(pc);}
        else if (strcmp(opcode, "tstne") == 0){pc = testne(pc);}
        else if (strcmp(opcode, "tstlt") == 0){pc = testlt(pc);}
        else if (strcmp(opcode, "tstle") == 0){pc = testle(pc);}
        else if (strcmp(opcode, "tstgt") == 0){pc = testgt(pc);}
        else if (strcmp(opcode, "tstge") == 0){pc = testge(pc);}  
    
        //fetchInstruction(pc, opcode, operand);
    } 
    printAll();
}

// discard rest of line (good for comments)
void discardline(FILE * fp)
{
    int newline;
    do
    {
        newline = fgetc(fp);
    } while ((char)newline != '\n' && (newline != EOF));
}
