
# Makefile
# Project IFJ19
#
# Březina Jindřich (xbrezi21@stud.fit.vutbr.cz)
# Gumančík Pavol (xguman01@stud.fit.vutbr.cz)
# Kotáb Dominik (xkotab01@stud.fit.vutbr.cz)
# Moravčík Tomáš (xmorav41@stud.fit.vutbr.cz)


OBJS	= list.o strings.o
SOURCE	= list.c strings.c
HEADER	= error.h list.h scanner.h stack.h strings.h
OUT	= final.out
CC	 = gcc
FLAGS	 = -g3 -c -Wall
LFLAGS	 =

#all: $(OBJS)
#	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

#final.out: $(OBJS)
#	$(CC) -g $(OBJS) -o $(OUT)
list.o: list.c
	$(CC) $(FLAGS) list.c

strings.o: strings.c
	$(CC) $(FLAGS) strings.c


clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)

debug: $(OUT)
	valgrind $(OUT)

valgrind: $(OUT)
	valgrind $(OUT)

valgrind_leakcheck: $(OUT)
	valgrind --leak-check=full $(OUT)

valgrind_extreme: $(OUT)
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --track-origins=yes --vgdb=yes $(OUT)
