#include "../../include/ds/zroc_stack.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stack_new(size_t element_size, size_t init_capacity, Zroc_Stack *out) {
  if (!out) {
    fputs("Error: Null \"out\".\n", stderr);
    return -1;
  }

  out->data = malloc(element_size * init_capacity);
  if (!out->data) {
    fprintf(stderr, "Error: Memory allocation failed in stack_new.\n");
    return -1;
  }

  out->size = 0;
  out->capacity = init_capacity;
  out->element_size = element_size;

  return 0;
}

int stack_push(Zroc_Stack *stack, void *element) {
  if (!stack || !element) {
    fputs("Error: Null stack or element in stack_push.\n", stderr);
    return -1;
  }

  if (stack->size >= stack->capacity) {
    size_t new_capacity = stack->capacity * 2;
    void *new_data = realloc(stack->data, stack->element_size * new_capacity);
    if (!new_data) {
      fputs("Error: Stack resize failed.\n", stderr);
      return -1;
    }
    stack->data = new_data;
    stack->capacity = new_capacity;
  }

  memcpy((char *)stack->data + (stack->size * stack->element_size), element,
         stack->element_size);
  stack->size++;

  return 0;
}

int stack_pop(Zroc_Stack *stack, void *out) {
  if (!stack || stack->size == 0) {
    fputs("Error: Stack is empty or null.\n", stderr);
    return -1;
  }

  void *src = (char *)stack->data + ((stack->size - 1) * stack->element_size);
  memcpy(out, src, stack->element_size);

  stack->size--;

  return 0;
}

void stack_free(Zroc_Stack *stack) {
  if (!stack || !stack->data)
    return;

  free(stack->data);
  stack->data = NULL;
  stack->size = 0;
  stack->capacity = 0;
}
