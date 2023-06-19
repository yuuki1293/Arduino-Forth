AC = bin/arduino-cli
AFLAGS = --fqbn
BOARD = arduino:avr:uno

all: compile

compile: src/src.ino
	$(AC) compile $(AFLAGS) $(BOARD) src