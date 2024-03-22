all:
	gcc -c test.c
	gnatmake -c library.adb
	gnatbind -n library.ali
	gnatlink library.ali test.o -o main