#ifndef ZROC_STACK
#define ZROC_STACK
#include "zroc_dynArray.h"
#include <stdio.h>

typedef struct {
  Zroc_DynArray *data;
  size_t size;
  size_t capacity;
  size_t element_size;
} Zroc_Stack;

int stack_new(size_t element_size, size_t init_capacity, Zroc_Stack *out);
int stack_push(Zroc_Stack *stack, void *element);
int stack_pop(Zroc_Stack *stack, void *out);
void stack_free(Zroc_Stack *stack);

#endif
