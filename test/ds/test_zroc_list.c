#include "../../include/ds/zroc_list.h"
#include "../zroc_testing.c"
#include "../zroc_testing.h"
#include <stdio.h>
#include <stdlib.h>

void test_list_operations(TestContext *tc) {
  Zroc_List list;

  // Initialize list
  test(tc, "List initialization", list_new(sizeof(int), 0, NULL, &list) == 0);
  test(tc, "List initial size", list.size == 0);
  test(tc, "List initial head is NULL", list.head == NULL);
  test(tc, "List initial tail is NULL", list.tail == NULL);

  // Adding elements
  int values[] = {10, 20, 30, 40, 50};
  for (int i = 0; i < 5; i++) {
    test(tc, "Adding element", list_add(&list, i, &values[i]) == 0);
  }
  test(tc, "List size after adding elements", list.size == 5);

  // Getting elements
  int fetched;
  for (int i = 0; i < 5; i++) {
    test(tc, "Getting element",
         list_get(&list, i, &fetched) == 0 && fetched == values[i]);
  }

  // Removing elements
  int removed = 0;
  test(tc, "Removing element at index 2", list_remove(&list, 2, &removed) == 0);
  test(tc, "List size after removal", list.size == 4);

  // Check if the remaining values are correct
  int expected_values[] = {10, 20, 40, 50};
  for (int i = 0; i < 4; i++) {
    test(tc, "Getting element after removal",
         list_get(&list, i, &fetched) == 0 && fetched == expected_values[i]);
  }

  // Out-of-bounds access tests
  test(tc, "Getting out-of-bounds element", list_get(&list, 10, &fetched) != 0);
  test(tc, "Removing out-of-bounds element", list_remove(&list, 10, &removed) != 0);

  // Free list
  list_free(&list);
  test(tc, "List free", list.size == 0 && list.head == NULL && list.tail == NULL);

  if (tc->failures > 0) {
    printf("\n%d/%d tests failed!\n", tc->failures, tc->count);
  } else {
    printf("\nAll tests passed!\n");
  }
}

int main() {
  TestContext tc = create_context();
  test_list_operations(&tc);
  return 0;
}
