/**
 * testtable.c
 *
 * Modified with permission from Dr. Fenwick's code.
 * Test file for the table class.
 *
 * @author Brian Clee
 * @version 3/18/2014
 */

#include <stdio.h>
#include "table.h"

void simpleTest(tableType);
void advancedTest(tableType);

int main()
{
    tableType table1;
    tableType table2;
    printf("Initializing tables for testing\n\n");
    initializeTable(&table1);
    initializeTable(&table2);

    simpleTest(table1);
    advancedTest(table2);

    return 0;
}

void simpleTest(tableType table)
{
    printf("==================================\n");
    printf("== Beginning simple table tests ==\n");
    printf("==================================\n");
    
    //stores
    printf("Storing 3 into A\n");
    store(&table, "A", 3);
    printf("Storing 4 into B\n");
    store(&table, "B", 4);
    printf("Storing 5 into C\n");
    store(&table, "C", 5);

    //retrieve and compare
    printf("Retrieving A...");
    int x = retrieve(&table, "A");
    if (x == 3)
        printf("success\n");
    else
        printf("** ERROR **\n");

    //retrieve and compare
    printf("Retrieving B...");
    x = retrieve(&table, "B");
    if (x == 4)
        printf("success\n");
    else
        printf("** ERROR **\n");

    //retrieve and compare
    printf("Retrieving C...");
    x = retrieve(&table, "C");
    if (x == 5)
        printf("success\n");
    else
        printf("** ERROR **\n");

    //retrieve and compare
    printf("Retrieving B...");
    x = retrieve(&table, "B");
    if (x == 4)
        printf("success\n");
    else
        printf("** ERROR **\n");

    //store replace
    printf("Storing 24 into B\n");
    store(&table, "B", 24);

    //retrieve and compare
    printf("Retrieving B...");
    x = retrieve(&table, "B");
    if (x == 24)
        printf("success\n");
    else
        printf("** ERROR **\n");

    //tests print
    printf("Table contents (should be A=3, B=24, C=5):\n");
    printTable(&table);
}

void advancedTest(tableType table)
{

}
