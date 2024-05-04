all: main
	
main: main.o
	g++ -o main main.o

main.o: main.cpp body/gf_child.hpp
	g++ -O3 -c main.cpp

gf.o: body/gf.cpp body/gf.hpp 
	g++ -O3 -c body/gf.cpp
