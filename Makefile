AC = arduino-cli
AFLAGS = --fqbn
BOARD = arduino:avr:uno
CC = g++
LD = g++
CFLAGS = -pedantic-errors -Wall -Werror -Wextra -ggdb -std=c++2a

all: compile

compile: src/src.ino
	$(AC) compile $(AFLAGS) $(BOARD) src

local: forth.o global.o next.o words.o
	$(LD) -o $@ $^

%.o: src/%.cpp src/%.hpp
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o main

.PHONY: clean