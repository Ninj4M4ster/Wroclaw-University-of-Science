all:
	gcc -c lib.c
	gnatmake -c main.adb
	gnatbind main.ali
	gnatlink main.ali lib.o

clean:
	rm *.o *.ali main