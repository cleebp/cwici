/**
 * table.h
 *
 * Modified with permission from Dr. Fenwick.
 *
 * @author Brian Clee
 * @version 3/18/2014
 */

#ifndef TABLE_H_
#define TABLE_H_

#define TABLE_SIZE 20
#define KEY_SIZE 20

//table entries
typedef struct
{
    //+1 as it is null terminated
    char key[KEY_SIZE+1];
    int value;
} tableEntry;

//table contains entries and the number of elements
typedef struct 
{
    int numItemsInUse;
    tableEntry entry[TABLE_SIZE];
} tableType;

//function prototypes.
void store(tableType *Xtable, char *key, int val);
int retrieve(tableType *Xtable, char *key);
void initializeTable(tableType *Xtable);
void printTable(tableType *Xtable);

#endif
