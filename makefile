default: 
	@echo "make targets are: stack, table, cwici, test1"

stack: teststack.c stack.h stack.c 
	gcc teststack.c stack.c -o teststack

table: testtable.c table.h table.c 
	gcc testtable.c table.c -o testtable

cwici: main.c stack.c stack.h table.c table.h instructions.c instructions.h
	gcc -g main.c stack.c table.c instructions.c -o cwici

test1: cwici test1.wic instructions.c instructions.h
	./run1.pl
	@echo "cat test1.diffs - pass on empty"
