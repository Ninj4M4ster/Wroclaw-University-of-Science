CFLAGS += -O3 -g3 -Wextra --pedantic -std=c11

run:
	./main

all: main

main: mastermind.o
	clang $(CFLAGS) -o main mastermind.o

mastermind.o: mastermind.c
	clang $(CFLAGS) -c mastermind.c

clean:
	rm -f main *.o *~