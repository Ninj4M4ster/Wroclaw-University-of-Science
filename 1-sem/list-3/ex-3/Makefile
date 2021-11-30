CFLAGS += -O3 -g3 -Wextra --pedantic -std=c11
LIBS += -lm

all: main

main: main.o phi.o nwd.o
	clang $(CFLAGS) -o main main.o phi.o nwd.o $(LIBS)

main.o: main.c
	clang $(CFLAGS) -c main.c

nwd.o: nwd.c
	clang $(CFLAGS) -c nwd.c

phi.o: phi.c
	clang $(CFLAGS) -c phi.c

clean:
	rm -f main *.o *~