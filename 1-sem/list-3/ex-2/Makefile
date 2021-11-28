all: main

main: main.o f.o
	clang -o main main.o f.o math.o

main.o: main.c
	clang -c main.c

f.o: f.c
	clang -c f.c

math.o: math.c
	clang -c math.c

clean:
	rm -f main *.o *~