CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g -O3 -march=native
DEPS = pmcgs.hpp clobber.hpp
OBJECTS = main.o clobber.o

.PHONY: all clean

all: clobber

clobber: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm clobber *.o