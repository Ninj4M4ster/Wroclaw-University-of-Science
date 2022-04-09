CFLAGS += -O3 -g3 -Wextra --pedantic -std=c11
LIBS += -lm

all: main

main: main.o newagent.o north.o south.o east.o west.o distance.o
	clang $(CFLAGS) -o main main.o newagent.o north.o south.o east.o west.o distance.o $(LIBS)

main.o: main.c
	clang $(CFLAGS) -c main.c

newagent.o: newagent.c
	clang $(CFLAGS) -c newagent.c

north.o: north.c
	clang $(CFLAGS) -c north.c

south.o: south.c
	clang $(CFLAGS) -c south.c

east.o: east.c
	clang $(CFLAGS) -c east.c

west.o: west.c
	clang $(CFLAGS) -c west.c

distance.o: distance.c
	clang $(CFLAGS) -c distance.c

clean:
	rm -f main *.o *~