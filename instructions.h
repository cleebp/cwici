/*
 * instructions.h
 *
 * Modified with permission from Dr. Fenwick.
 *
 * @author Brian Clee
 * @version 3/19/14
 */

#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

//used in instruction.c and main
#define OPCODE_SIZE 6 
#define OPERAND_SIZE 21

int hasOperand(char * opcode);
void insertInstruction(int address, char * opcode, char * operand);
int fetchInstruction(int address, char * opcode, char * operand);
void initialize();
void printSymbolTable();
void printAll();
void printInstrTable();

//interpreter prototypes
int nop(int);
int add(int);
int sub(int);
int mul(int);
int divide(int); 
int get(int, char * operand);
int put(int, char * operand);
int push(int, char * operand);
int pop(int, char * operand);
int not(int);
int and(int);
int or(int);
int testeq(int);
int testne(int);
int testlt(int);
int testle(int);
int testgt(int);
int testge(int);
int jump(int, char * operand);
int jf(int, char * operand);
int halt(int);
#endif
