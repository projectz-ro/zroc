CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g
SRC = src/ds/zroc_stack.c
TESTS = $(shell find test/ -name "*.c")
OUT = bin/tests

test: $(SRC) $(TESTS)
	$(CC) $(CFLAGS) $(SRC) $(TESTS) -o $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)

