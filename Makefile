CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g
SRC = src/ds/zroc_stack.c
TESTS = $(shell find test/ -name "*.c")
OUT = bin/tests

test_ds_array: test/ds/test_zroc_array.c   
test_ds_dynArray: test/ds/test_zroc_dynArray.c   
test_ds_stack: test/ds/test_zroc_stack.c   

clean:
	rm -f $(OUT)

