all: main

.PHONY: main


main:
	g++ main.cpp -Iinclude/ -Llib/ -lfreeglut -lfreeglut_static -lopengl32 -o main
	./main -i test.inp