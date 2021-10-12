CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: main

main: main.c
	gcc $(CFLAGS) main.c -o main $(LDFLAGS)

clean:
	rm -f main
