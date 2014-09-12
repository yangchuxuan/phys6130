CFLAGS= -Wall -g -lm -std=c99
test : main.o
	gcc $(CFLAGS) -o test main.o
main.o : main.c
	gcc $(CFLAGS) -c main.c
clean:
	rm test main.o
