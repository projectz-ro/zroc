#include "../../include/ds/zroc_stack.h"
#include "../zroc_testing.c"
#include "../zroc_testing.h"
#include <stdio.h>
#include <stdlib.h>

void test_stack_operations(TestContext *tc) {
  Zroc_Stack stack;
  size_t init_capacity = 4;

  // Stack initialization
  test(tc, "Stack initialization",
       stack_new(sizeof(int), init_capacity, &stack) == 0);
  test(tc, "Stack initial capacity", stack.capacity == init_capacity);
  test(tc, "Stack initial size", stack.size == 0);

  // Pushing elements
  int values[] = {10, 20, 30, 40, 50};
  for (int i = 0; i < 5; i++) {
    test(tc, "Pushing element", stack_push(&stack, &values[i]) == 0);
  }
  test(tc, "Stack size after pushes",
       stack.size == 5); // One push should trigger resize

  // Test popping elements
  int popped;
  test(tc, "Popping element", stack_pop(&stack, &popped) == 0 && popped == 50);
  test(tc, "Stack size after pop", stack.size == 4);
  test(tc, "Popping another element",
       stack_pop(&stack, &popped) == 0 && popped == 40);
  test(tc, "Stack size after second pop", stack.size == 3);

  // Popping until empty
  test(tc, "Popping from non-empty stack", stack_pop(&stack, &popped) == 0);
  test(tc, "Popping from non-empty stack", stack_pop(&stack, &popped) == 0);
  test(tc, "Popping from non-empty stack", stack_pop(&stack, &popped) == 0);
  test(tc, "Stack size after popping all elements", stack.size == 0);

  // Popping from empty stack
  test(tc, "Popping from empty stack", stack_pop(&stack, &popped) != 0);

  // Free stack
  stack_free(&stack);
  test(tc, "Stack free",
       stack.data == NULL && stack.capacity == 0 && stack.size == 0);

  if (tc->failures > 0) {
    printf("\n%d/%d tests failed!\n", tc->failures, tc->count);
  } else {
    printf("\nZroc Stack: All tests passed!\n");
  }
}

int main() {
  TestContext tc = create_context();
  /* suppress_stderr(&tc); */
  test_stack_operations(&tc);
  /* restore_stderr(&tc); */
  return 0;
}
