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

runAll: cwici
	./runAll.pl
	@echo "just ran all the tests..."

test1: cwici ./tests/test1.wic
	./tests/run1.pl
	@echo "Output and tables/stack from cwici run are above"

test2: cwici ./tests/test2.wic
	./tests/run2.pl
	@echo "Output and tables/stack from cwici run are above"

part4-1: cwici ./tests/test4-1.wic
	./tests/run4-1.pl
	@echo "Output and tables/stack from cwici run are above"

part4-2: cwici ./tests/test4-2.wic
	./tests/run4-2.pl
	@echo "Output and tables/stack from cwici run are above"

part4-3: cwici ./tests/test4-3.wic
	./tests/run4-3.pl
	@echo "Output and tables/stack from cwici run are above"

part4-4: cwici ./tests/test4-4.wic
	./tests/run4-4.pl
	@echo "Output and tables/stack from cwici run are above"

part4-5: cwici ./tests/test4-5.wic
	./tests/run4-5.pl
	@echo "Output and tables/stack from cwici run are above"

part4-6: cwici ./tests/test4-6.wic
	./tests/run4-6.pl
	@echo "Output and tables/stack from cwici run are above"

part4-7: cwici ./tests/test4-7.wic
	./tests/run4-7.pl
	@echo "Output and tables/stack from cwici run are above"

part4-8: cwici ./tests/test4-8.wic
	./tests/run4-8.pl
	@echo "Output and tables/stack from cwici run are above"

max: cwici ./tests/max.wic
	./tests/runMax.pl
	@echo "Output and tables/stack from cwici run are above"

numbin: cwici ./tests/numbin.wic
	./tests/runBin.pl
	@echo "Output and tables/stack from cwici run are above"
