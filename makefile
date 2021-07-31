CC=gcc
CFLAGS=-Wall
DEPS = antipolish.h stack.h

antipolish: compare.o molon.lb.o getop.o stack.o antipolish.o
	$(CC) compare.o molon.lb.o getop.o stack.o antipolish.o -o antipolish.elf -lm
