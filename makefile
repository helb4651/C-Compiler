BIN  = c-
CC   = g++
CFLAGS = -DCPLUSPLUS -g  -x c # for use with C++ if file ext is .c
SRCS = $(BIN).y $(BIN).l scanType.h globals.h util.h util.cpp symbolTable.h symbolTable.cpp
OBJS = lex.yy.o $(BIN).tab.o util.o symbolTable.o
LIBS = -lm

$(BIN): $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) $(LIBS) -o $(BIN)

$(BIN).tab.h $(BIN).tab.c: $(BIN).y
	bison -v -t -d $(BIN).y   # -d supplies defines file

lex.yy.c: $(BIN).l $(BIN).tab.h
	flex $(BIN).l  # -d debug

util.o: util.cpp util.h globals.h
	$(CC) $(CFLAGS) -c util.cpp

symbolTable.o: symbolTable.cpp symbolTable.h
	$(CC) $(CFLAGS) -c symbolTable.cpp

all:
	touch $(SRCS)
	make

clean:
	rm -f $(OBJS) $(BIN) $(BIN).output lex.yy.c $(BIN).tab.h $(BIN).tab.c $(BIN).tar *~

tar:
	tar -cvf helbling.tar $(SRCS) makefile
