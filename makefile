CC = gcc
CFLAGS = -Wall
DEPS = antipolish.h
OBJ = compare.o molon.lb.o getop.o stack.o antipolish.o
OBJPILE = $(CC) $(CFLAGS) -c -o $@ $<

antipolish.o : antipolish.c $(DEPS)
	$(OBJPILE)

stack.o : stack.c $(DEPS)
	$(OBJPILE)

getop.o : getop.c stack.h $(DEPS)
	$(OBJPILE)

%.o: %.c 
	 $(CC) $(CFLAGS) -c -o $@ $<

antipolish: $(OBJ)
	$(CC) $(OBJ) -o antipolish.elf -lm
