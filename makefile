# Makefile
CXX_FLAG = --std=c++17 -g

project2_first.out: project2_first.o
	g++ $(CXX_FLAG) project2_first.o -o project2_first.out

project2_second.out: project2_second.o
	g++ $(CXX_FLAG) project2_second.o -o project2_second.out

project2_first.o: project2_first.cpp
	g++ -c $(CXX_FLAG) project2_first.cpp

project2_second.o: project2_second.cpp
	g++ -c $(CXX_FLAG) project2_second.cpp

clean:
	rm -f project2_first project2_second *.o