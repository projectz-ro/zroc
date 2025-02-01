#include "../../include/ds/zroc_stack.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int new_stack(size_t unit_size, size_t init_capacity, Zroc_Stack *out) {
  if (!out) {
    fputs("Error: Null \"out\".\n", stderr);
    return -1;
  }
  out->element_size = unit_size;
  out->data = malloc(out->element_size * init_capacity);
  if (!out->data) {
    fputs("Error: Memory allocation for new_stack failed.\n", stderr);
    return -1;
  }
  out->size = 0;
  out->capacity = init_capacity;

  return 0;
}

int stack_push(Zroc_Stack *stack, void *element) {
  if (!stack || !element) {
    fputs("Error: Null stack or element in stack_push.\n", stderr);
    return -1;
  }
  if (stack->size == stack->capacity) {
    if (stack->capacity > SIZE_MAX / 2) {
      fputs("Error: Stack capacity overflow in stack_push.\n", stderr);
      return -1;
    }
    stack->capacity *= 2;
    void *temp_data =
        realloc(stack->data, stack->element_size * stack->capacity);
    if (!temp_data) {
      fputs("Error: Memory reallocation for stack push failed.\n", stderr);
      return 1;
    }
    stack->data = temp_data;
  }
  char *dest = (char *)stack->data + (stack->size * stack->element_size);
  memcpy(dest, element, stack->element_size);
  stack->size++;
  return 0;
}

int stack_pop(Zroc_Stack *stack, void *out) {
  if (stack->size == 0) {
    fputs("Error: Stack is empty.\n", stderr);
    return -1;
  }
  void *last_element =
      (char *)stack->data + (stack->size - 1) * stack->element_size;

  memcpy(out, last_element, stack->element_size);
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
  stack = NULL;
}
