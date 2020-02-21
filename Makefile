CC=g++

tree_make: tools.cpp algo.cpp drawings.cpp main.cpp
	$(CC) -o a.out tools.cpp algo.cpp drawings.cpp main.cpp -lglut -lGL