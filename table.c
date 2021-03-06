/**
 * table.c
 *
 * Modified with permission from Dr. Fenwick.
 *
 * This class contains the implementation of the 
 * symbol table. A table contains entries which are 
 * key value pairs.
 *
 * @author Brian Clee
 * @version 3/18/14
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "table.h"

void initializeTable(tableType *Xtable)
{
    Xtable->numItemsInUse = 0;
}

/**
 * When storing, we check if the variable is already present in the table.
 * If it is, rewrite the value as opposed to creating a new entry.
 */
void store(tableType *Xtable, char *key, int val){
    int i;
    for(i = 0; i < Xtable->numItemsInUse; i++)
    {
        //First pass through to see if value is already in the table.
        if(strcmp(key,Xtable->entry[i].key) == 0)
        {
            //If it is, overwrite the value and stop execution.
            Xtable->entry[i].value = val;
            return;
        }
    }

    // If reach this point then the value is not already present.
    // Need some way to remember the current position.
    strncpy(Xtable->entry[i].key, key, 20);
    Xtable->entry[i].value = val;
    Xtable->numItemsInUse++;
}

int retrieve(tableType *Xtable, char *key)
{
    //Search for entry. If found return value. If not, error occurred.
    int i;
    for(i = 0; i < Xtable->numItemsInUse; i++)
    {
        //First pass through to see if value is already in the table.
        if(strcmp(key,Xtable->entry[i].key) == 0)
	        return Xtable->entry[i].value;
    }
    
    printf("ERROR, non-existant key %s in table.\n", key);
    exit(1);
    return 0; 
}

//for debugging
void printTable(tableType * Xtable)
{
    int i;
    if(Xtable->numItemsInUse == 0)
    {
        printf("Table is empty\n");
    }
    else
    {
        for(i = 0; i < Xtable->numItemsInUse; i++)
        {
            printf("%s = %d\n", Xtable->entry[i].key, Xtable->entry[i].value);
        }
    }
}
