CFLAGS=  -g -lm -Wall -Wextra -std=c++11
test : main.o
	g++ $(CFLAGS) -o test main.o
main.o : main.cpp
	g++ $(CFLAGS) -c main.cpp
clean:
	rm test main.o
