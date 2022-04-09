CFLAGS += -O3 -g3 -Wextra --pedantic -std=c11

all: main

main: main.o match.o
	clang $(CFLAGS) -o main main.o match.o

main.o: main.c
	clang $(CFLAGS) -c main.c

match.o: match.c
	clang $(CFLAGS) -c match.c

clean:
	rm -f main *.o *~