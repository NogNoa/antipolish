CC=gcc
CFLAGS=-Wall
#DEPS = antipolish.h stack.h

antipolish: compare.c molon.lb.c getop.c stack.c antipolish.c
	$(CC) compare.c molon.lb.c getop.c stack.c antipolish.c -o antipolish.elf -lm
