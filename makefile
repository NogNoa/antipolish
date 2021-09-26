CC = gcc
CFLAGS = -Wall
DEPS = antipolish.h
APA = antipolish-argument
ODIR = obj
_OBJ = compare.o getop.o stack.o antipolish.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))
OBJA = $(ODIR)/$(APA).o $(ODIR)/stack.o $(ODIR)/getop-argument.o
OBJPILE = $(CC) $(CFLAGS) -c -o $@ $<
COMPILE = $(CC) $^ -o $@.elf $(CFLAGS)  -lm

$(ODIR)/antipolish.o : antipolish.c $(DEPS)
	$(OBJPILE)

$(ODIR)/stack.o : stack.c $(DEPS)
	$(OBJPILE)

$(ODIR)/getop.o : getop.c stack.h $(DEPS)
	$(OBJPILE)

$(ODIR)/$(APA).o : $(APA).c $(APA).h
	$(OBJPILE)

$(ODIR)/getop-arguments.o: getop-arguments.c $(APA).h stack.h

$(ODIR)/%.o: %.c 
	 $(OBJPILE)

antipolish: $(OBJ)
	$(COMPILE)

apa: $(OBJA)
	$(COMPILE)
