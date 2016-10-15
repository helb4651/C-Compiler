BIN  = c-
CC   = g++
SRCS = $(BIN).y $(BIN).l scanType.h globals.h semantic.h semantic.cpp symbolTable.h symbolTable.cpp printtree.cpp printtree.h typeingHelpers.h typeingHelpers.cpp
OBJS = lex.yy.o $(BIN).tab.o semantic.o symbolTable.o printtree.o typingHelpers.o
LIBS = -lm

$(BIN): $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) $(LIBS) -o $(BIN)

$(BIN).tab.h $(BIN).tab.c: $(BIN).y
	bison -v -t -d $(BIN).y   # -d supplies defines file

lex.yy.c: $(BIN).l $(BIN).tab.h
	flex $(BIN).l  # -d debug

semantic.o: semantic.cpp semantic.h globals.h
	$(CC) $(CFLAGS) -c semantic.cpp

printtree.o: printtree.cpp printtree.h globals.h
	$(CC) $(CFLAGS) -c printtree.cpp

symbolTable.o: symbolTable.h symbolTable.cpp
	$(CC) $(CFLAGS) -c symbolTable.cpp

typingHelpers.o: typingHelpers.h typingHelpers.cpp
	$(CC) $(CFLAGS) -c typingHelpers.cpp

all:
	touch $(SRCS)
	make

clean:
	rm -f $(OBJS) $(BIN) $(BIN).output lex.yy.c $(BIN).tab.h $(BIN).tab.c $(BIN).tar *~

pdf:
	c-.y c-.l makefile
	mktex c-.y
	mv c-.pdf c--y.pdf
	mktex c-.l
	mv c-.pdf c--l.pdf
	mktex makefile
	save c--l.pdf c--y.pdf makefile.pdf
	rm *.tex

tar:
	tar -cvf $(BIN).tar $(SRCS) makefile
