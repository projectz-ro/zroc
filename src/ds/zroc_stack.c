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

  out->data = malloc(sizeof(Zroc_DynArray));
  if (!out->data) {
    fprintf(stderr, "Error: Memory allocation for %p in new_stack failed.\n",
            (void *)out);
    return -1;
  }

  int error = dynArray_new(element_size, init_capacity, out->data);
  if (error) {
    fputs("Error: Failed to initialize stack using dynamic array.\n", stderr);
    return -1;
  }

  out->size = out->data->size;
  out->capacity = out->data->capacity;
  out->element_size = element_size;

  return 0;
}

int stack_push(Zroc_Stack *stack, void *element) {
  if (!stack || !element) {
    fputs("Error: Null stack or element in stack_push.\n", stderr);
    return -1;
  }
  int error = dynArray_set(stack->data, stack->data->size, element);
  if (error) {
    fprintf(stderr,
            "Error: Failed to push element: %p onto stack: %p in stack_push.\n",
            (void *)element, (void *)stack);
    return -1;
  }
  stack->size = stack->data->size;
  stack->capacity = stack->data->capacity;

  return 0;
}

int stack_pop(Zroc_Stack *stack, void *out) {
  if (stack->size == 0) {
    fputs("Error: Stack is empty.\n", stderr);
    return -1;
  }
  int idx = stack->data->size > 0 ? stack->data->size - 1 : 0;
  int error = dynArray_get(stack->data, idx, out);
  if (error) {
    fprintf(stderr,
            "Error: Failed to pop element from stack: %p in stack_pop.\n",
            (void *)stack);
    return -1;
  }
  stack->data->size--;
  stack->size = stack->data->size;

  return 0;
}

void stack_free(Zroc_Stack *stack) {
  if (!stack || !stack->data)
    return;
  dynArray_free(stack->data);
  free(stack->data);
  stack->data = NULL;
  stack->size = 0;
  stack->capacity = 0;
}
