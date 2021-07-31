CC = gcc
CFLAGS = -Wall
DEPS = antipolish.h
ODIR = obj
_OBJ = compare.o molon.lb.o getop.o stack.o antipolish.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))
OBJPILE = $(CC) $(CFLAGS) -c -o $@ $<

$(ODIR)/antipolish.o : antipolish.c $(DEPS)
	$(OBJPILE)

$(ODIR)/stack.o : stack.c $(DEPS)
	$(OBJPILE)

$(ODIR)/getop.o : getop.c stack.h $(DEPS)
	$(OBJPILE)

$(ODIR)/%.o: %.c 
	 $(OBJPILE)

antipolish: $(OBJ)
	$(CC) $(OBJ) -o $@.elf $(CFLAGS)  -lm
