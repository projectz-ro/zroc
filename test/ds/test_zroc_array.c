#include "../../include/ds/zroc_array.h"
#include "../zroc_testing.c"
#include "../zroc_testing.h"
#include <stdio.h>
#include <stdlib.h>

void test_array_operations(TestContext *tc) {
  Zroc_Array array;
  size_t init_capacity = 4;

  // Array initialization
  test(tc, "Array initialization",
       array_new(sizeof(int), init_capacity, &array) == 0);
  test(tc, "Array initial capacity", array.capacity == init_capacity);
  test(tc, "Array initial size", array.size == 0);

  // Setting elements
  int values[] = {10, 20, 30, 40};
  for (int i = 0; i < 4; i++) {
    test(tc, "Setting element", array_set(&array, i, &values[i]) == 0);
  }

  // Getting elements
  int fetched;
  for (int i = 0; i < 4; i++) {
    test(tc, "Getting element",
         array_get(&array, i, &fetched) == 0 && fetched == values[i]);
  }

  int new_value = 60;

  // Check out-of-bounds access (getting element from index >= size)
  int out_of_bounds_fetched;
  test(tc, "Out of bounds get",
       array_get(&array, 6, &out_of_bounds_fetched) != 0);

  // Check setting element at an out-of-bounds index
  test(tc, "Out of bounds set", array_set(&array, 7, &new_value) != 0);

  // Free array
  array_free(&array);
  test(tc, "Array free",
       array.data == NULL && array.capacity == 0 && array.size == 0);

  if (tc->failures > 0) {
    printf("\n%d/%d tests failed!\n", tc->failures, tc->count);
  } else {
    printf("\nAll tests passed!\n");
  }
}

int main() {
  TestContext tc = create_context();
  test_array_operations(&tc);
  return 0;
}
