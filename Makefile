ALL: COMPILE

CFLAGS = -O3

COMPILE: src/*.c
	gcc -o build/gplgen $(CFLAGS) src/*.c

INSTALL: COMPILE
	cp -rf build/gplgen /usr/bin/gplgen

TEST:
	build/gplgen -p test -y 2024 -a "Lilly H. St Claire" -d test of GPLGEN -s -r "Visual Basic" --prepend --dontstandout test.vb
