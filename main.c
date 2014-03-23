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

    // All done, how about some debugging output...
    printf("\nSymbol Table\n");
    printf("------------\n");
    printSymbolTable();

    printf("\nProgram halted\n");
}

void readInstructions(FILE * fp)
{
    int eof, address = 0;
    char *opcode;
    char *operand;

    //infinite loop fetch until fscanf returns EOF or -1
    while(1 > 0)
    {
        //read opcode
        eof = fscanf(fp, "%s", opcode);
        if(eof == EOF)
            break;
        
        //check if opcode expects an operand and read if it does
        if(hasOperand(opcode) == 1)
        {
            fscanf(fp, "%s", operand);
        }
        else
        {
            operand = NULL;
        }

        //insert aqcuired opcode/operand at address and incr address
        insertInstruction(address, opcode, operand);
        address++;

        //discard rest of the current line in case of comments
        discardline(fp);
    }

    printf("wic isntructions read/insert has completed...\n");
}

void execute()
{

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
