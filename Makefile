CFLAGS = -O3 -std=c++11 -Wall

all: proj

proj: p1.cpp
	g++ $(CFLAGS) p1.cpp -o p1 -lm

clean:
	rm -f *.o p1

run: proj
	./p1
