default: 
	@echo "make targets are: stack, table, cwici, test1, test2"

stack: teststack.c stack.h stack.c 
	gcc teststack.c stack.c -o teststack

table: testtable.c table.h table.c 
	gcc testtable.c table.c -o testtable

cwici: main.c stack.c stack.h table.c table.h instructions.c instructions.h
	gcc -g main.c stack.c table.c instructions.c -o cwici

test1: cwici test1.wic
	./run1.pl
	@echo "cat test1.diffs - pass on empty"

test2: cwici test2.wic
	./run2.pl
	@echo "cat test2.diffs - pass on empty"
