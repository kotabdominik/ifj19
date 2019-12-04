
# Makefile
# Project IFJ19
#
# Březina Jindřich (xbrezi21@stud.fit.vutbr.cz)
# Gumančík Pavol (xguman01@stud.fit.vutbr.cz)
# Kotáb Dominik (xkotab01@stud.fit.vutbr.cz)
# Moravčík Tomáš (xmorav41@stud.fit.vutbr.cz)


SOURCE	= list.c strings.c scanner.c tokenStack.c symtable.c parser.c
HEADER	= error.h list.h scanner.h stack.h strings.h symtable.h parser.h tokenStack.h
CC	 = gcc

all: $(OBJS)
	$(CC) -g parser.c -o parser

clean:
	rm -f $(OBJS) $(OUT) parser

run:
	./parser

int:
	./parser <txt.txt >str.out
	./ic19int str.out
