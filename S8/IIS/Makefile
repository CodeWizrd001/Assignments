CC = g++
CFLAGS = -g -O2 -std=c++11 -pthread -march=native -lntl -lgmp -lm -lcrypto -lssl
all: $(patsubst %.cpp, %.out, $(wildcard *.cpp))
%.out: %.cpp Makefile
	$(CC) $< -o $@ $(CFLAGS)
clean:
	rm *.out 