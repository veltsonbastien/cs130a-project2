# Makefile
CXX_FLAG += --std=c++11 -g

all: project2_first.out project2_second.out

project2_first.out: project2_first.o hash24.o dictionary.o
	g++ $(CXX_FLAG) -o project2_first.out project2_first.o hash24.o dictionary.o

project2_second.out: project2_second.o hash24.o dictionary.o
	g++ $(CXX_FLAG) -o project2_second.out project2_second.o hash24.o dictionary.o

project2_first.o: project2_first.cpp
	g++ -c $(CXX_FLAG) project2_first.cpp
	
project2_second.o: project2_second.cpp
	g++ -c $(CXX_FLAG) project2_second.cpp

dictionary.o: dictionary.cpp
	g++ -c $(CXX_FLAG) dictionary.cpp

hash24.o: hash24.cpp	
	g++ -c $(CXX_FLAG) hash24.cpp

clean:
	rm -f project2_first project2_second dictionary hash24 *.o *.out *.gch