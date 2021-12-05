all: main

main: main.o palindrom.o
	gcc -o main main.o palindrom.o

main.o: main.c
	gcc -c main.c

palindrom.o: palindrom.c
	gcc -c palindrom.c

clean:
	rm -f main *.o *~