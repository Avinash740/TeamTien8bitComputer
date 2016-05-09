
vasm: vasm.c y.tab.o symtab.o misc.o init.o codegen.o gvars.h
	gcc vasm.c *.o -ly -ll -o vasm

symtab.o: symtab.c gvars.h
	gcc symtab.c -c

init.o: init.c gvars.h
	gcc init.c -c

misc.o: misc.c gvars.h
	gcc misc.c -c

codegen.o: codegen.c gvars.h
	gcc codegen.c -c

y.tab.o: y.tab.c lex.yy.c gvars.h
	gcc y.tab.c -c

y.tab.c: vasm.yacc
	yacc vasm.yacc

lex.yy.c: vasm.lex
	lex vasm.lex

clean:
	rm *.o
	rm y.tab.c
	rm lex.yy.c
