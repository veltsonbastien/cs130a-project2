# Makefile
CXX_FLAG += --std=c++11 -g

project2_first.out: project2_first.o
	g++ project2_first.o hash24.o -o project2_first.out

project2_second.out: project2_second.o
	g++ project2_second.o -o project2_second.out

project2_first.o: project2_first.cpp
	g++ -c project2_first.cpp project2_first.h hash24.h 
	g++ -c hash24.cpp hash24.h

project2_second.o: project2_second.cpp
	g++ -c project2_second.cpp

clean:
	rm -f project2_first project2_second hash24 *.o *.out *.gch