default: 
	@echo "make targets are: stack, table, cwici, test"

stack: teststack.c stack.h stack.c 
	gcc teststack.c stack.c -o teststack

table: testtable.c table.h table.c 
	gcc testtable.c table.c -o testtable

cwici: main.c stack.c stack.h table.c table.h instructions.c instructions.h
	gcc main.c stack.c table.c instructions.c -o testwici

test: cwici testfile.wic
	cwici testfile.wic >! testfile.out
	diff -b -B testfile.wic testfile.wic >! testfile.diffs
	@echo "less testfile.diffs - pass on empty"
