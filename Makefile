all: exe

exe: astar.cpp main.cpp
	g++ -fopenmp -o exe -O3 astar.cpp main.cpp -lm
.PHONY: clean
clean:
	rm exe
