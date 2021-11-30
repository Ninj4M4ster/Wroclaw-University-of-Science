CFLAGS += -O3 -g3 -Wextra --pedantic -std=c11
LIBS += -lm

all: main

main: main.o f.o
	clang $(CFLAGS) -o main main.o rozwiazanie.o f.o $(LIBS)

main.o: main.c
	clang $(CFLAGS) -c main.c

rozwiazanie.o: rozwiazanie.c
	clang $(CFLAGS) -c rozwiazanie.c

f.o: f.c
	clang $(CFLAGS) -c f.c

clean:
	rm -f main *.o *~