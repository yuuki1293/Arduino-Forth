AC = arduino-cli
AFLAGS = --fqbn
BOARD = arduino:avr:uno
PORT = COM8
CC = g++
LD = g++
CFLAGS = -pedantic-errors -Wall -Werror -Wextra -ggdb -g3 -std=c++2a
OBJDIR = obj
MODULES = src

all: compile

compile: $(MODULES)/src.ino
	$(AC) compile $(AFLAGS) $(BOARD) src

upload: $(MODULES)/src.ino
	$(AC) upload $(AFLAGS) $(BOARD) -p $(PORT) src

local: $(foreach src, forth.o global.o next.o words.o lib.o, $(OBJDIR)/$(src))
	$(LD) -o $@ $^

$(OBJDIR)/%.o: $(MODULES)/%.cpp $(MODULES)/%.hpp $(OBJDIR) 
	$(CC) $(CFLAGS) -D LOCAL -o $@ -c $<

$(OBJDIR):
	mkdir -p $@

clean:
	rm -f *.o main

.PHONY: clean