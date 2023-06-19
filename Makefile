AC = bin/arduino-cli
AFLAGS = --fqbn
BOARD = arduino:avr:uno

all: compile

compile: main/main.ino
	$(AC) compile $(AFLAGS) $(BOARD) main