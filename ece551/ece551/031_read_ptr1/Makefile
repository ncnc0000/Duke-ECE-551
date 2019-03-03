cc = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -Werror

test: test.c
	$(cc) $(CFLAGS) -o test test.c

.PHONY: clean
clean:
	rm -f test *.o *.c~
