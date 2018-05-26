CC = gcc
CFLAGS = -Wall
DEPS = token.h lex.h
OBJ = main.o token.o lex.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

