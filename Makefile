ALL: COMPILE

CFLAGS = -O3

COMPILE: src/*.c
	gcc -o build/gplgen $(CFLAGS) src/*.c
