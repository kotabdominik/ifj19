
# Makefile
# Project IFJ19
#
# Březina Jindřich (xbrezi21@stud.fit.vutbr.cz)
# Gumančík Pavol (xguman01@stud.fit.vutbr.cz)
# Kotáb Dominik (xkotab01@stud.fit.vutbr.cz)
# Moravčík Tomáš (xmorav41@stud.fit.vutbr.cz)

PROJ = parser
SOURCE	= expressions.c generator.c parser.c scanner.c stack.c strings.c symtable.c tokenStack.c list.c
CC	 = gcc
WARNINGS = -Wall -pedantic -Wextra

all: $(PROJ)

$(PROJ) : $(SOURCE)
	$(CC) -o $(PROJ) $(SOURCE) -lm -g

warnings:
	$(CC) -o $(PROJ) $(SOURCE) $(WARNINGS) -lm -g

clean:
	rm -f $(OBJS) $(OUT) $(PROJ)

run:
	make all
	./$(PROJ)

int:
	make all
	./$(PROJ) <txt.txt >str.out
	./ic19int str.out
