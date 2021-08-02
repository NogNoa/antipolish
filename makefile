CC = gcc
CFLAGS = -Wall
DEPS = antipolish.h
APA = antipolish-argument
ODIR = obj
_OBJ = compare.o molon.lb.o getop.o stack.o antipolish.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))
OBJA = $(ODIR)/$(APA).o $(ODIR)/stack.o $(ODIR)/getop-argument.o
OBJPILE = $(CC) $(CFLAGS) -c -o $@ $<

$(ODIR)/antipolish.o : antipolish.c $(DEPS)
	$(OBJPILE)

$(ODIR)/stack.o : stack.c $(DEPS)
	$(OBJPILE)

$(ODIR)/getop.o : getop.c stack.h $(DEPS)
	$(OBJPILE)

$(ODIR)/$(APA).o : $(APA).c $(APA).h
	$(OBJPILE)


$(ODIR)/%.o: %.c 
	 $(OBJPILE)

antipolish: $(OBJ)
	$(CC) $(OBJ) -o $@.elf $(CFLAGS)  -lm

apa: $(OBJA)
	$(CC) $(OBJA) -o $@.elf $(CFLAGS)  -lm
