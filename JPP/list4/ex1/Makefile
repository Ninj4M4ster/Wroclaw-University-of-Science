all: main
	
main: main.o gf.o
	g++ -o main main.o

main.o: main.cpp body/gf_child.hpp
	g++ -c main.cpp

gf.o: body/gf.cpp body/gf.hpp 
	g++ -c body/gf.cpp

user.o: user/user.cpp user/user.hpp
	g++ -c user/user.cpp

dh_setup.o: dh_setup/dh_setup.cpp dh_setup/dh_setup.hpp
	g++ -c dh_setup/dh_setup.cpp