SHELL=/bin/sh

CC=gcc
SRC=parser.c lexer.c main.c mem.c gen.c symtab.c heap.c yyerror.c message.c link.c
OBJ=$(SRC:%.c=%.o)

YFLAGS = -d
YACC = bison
LEX = flex
CFLAGS =  -DHAVE_CONFIG -include boolean.h 

TARGET=vcc

$(TARGET): $(OBJ) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) -lfl
	
install:
	rm -f $(OBJ) parser.c lexer.c 
	mv $(TARGET) ../vcc

main.o: config.h

parser.o: parser.c parser.y

parser.c: parser.y
	$(YACC) $(YFLAGS) $?
	mv -f parser.tab.c $@

parser.y: symtab.h mem.h gen.h

lexer.c: lexer.l parser.tab.h

mem.o: mem.h symtab.h

gen.o: gen.h symtab.h machine.h

heap.o: heap.h

symtab.o: symtab.h

link.o: symtab.h


clean:
	rm -f $(OBJ)
	rm -f lexer.c
	rm -f parser.c
	rm -f parser.tab.*
	rm -f $(TARGET)
	
uninstall: clean
	rm -f ../vcc
