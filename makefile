default: 
	@echo "make targets are: stack, table, cwici, test1, test2..."
	@echo "and the part4 increments: part4-1, part4-2, part4-3, part4-4,"
	@echo "part4-5, part4-6, part4-7, part4-8, max, numbin"

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

part4-1: cwici test4-1.wic
	./run4-1.pl
	@echo "Output and tables/stack from cwici run are above"

part4-2: cwici test4-2.wic
	./run4-2.pl
	@echo "Output and tables/stack from cwici run are above"

part4-3: cwici test4-3.wic
	./run4-3.pl
	@echo "Output and tables/stack from cwici run are above"

part4-4: cwici test4-4.wic
	./run4-4.pl
	@echo "Output and tables/stack from cwici run are above"

part4-5: cwici test4-5.wic
	./run4-5.pl
	@echo "Output and tables/stack from cwici run are above"

part4-6: cwici test4-6.wic
	./run4-6.pl
	@echo "Output and tables/stack from cwici run are above"

part4-7: cwici test4-7.wic
	./run4-7.pl
	@echo "Output and tables/stack from cwici run are above"

part4-8: cwici test4-8.wic
	./run4-8.pl
	@echo "Output and tables/stack from cwici run are above"

max: cwici max.wic
	./runMax.pl
	@echo "Output and tables/stack from cwici run are above"

numbin: cwici numbin.wic
	./runBin.pl
	@echo "Output and tables/stack from cwici run are above"
