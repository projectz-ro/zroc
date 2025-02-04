#include "../../include/ds/zroc_dynArray.h"
#include "../zroc_testing.c"
#include "../zroc_testing.h"
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void test_dynArray_operations(TestContext *tc) {
  Zroc_DynArray dynArray;
  size_t init_capacity = 4;

  // Dynamic Array initialization
  test(tc, "Dynamic Array initialization",
       dynArray_new(sizeof(int), init_capacity, &dynArray) == 0);
  test(tc, "Dynamic Array initial capacity",
       dynArray.capacity == init_capacity);
  test(tc, "Dynamic Array initial size", dynArray.size == 0);

  // Setting elements
  int values[] = {10, 20, 30, 40, 50};
  for (int i = 0; i < 5; i++) {
    test(tc, "Setting element", dynArray_set(&dynArray, i, &values[i]) == 0);
  }
  test(tc, "Dynamic Array size after setting",
       dynArray.size == 5); // Array should have size 5

  // Getting elements
  int fetched;
  for (int i = 0; i < 5; i++) {
    test(tc, "Getting element",
         dynArray_get(&dynArray, i, &fetched) == 0 && fetched == values[i]);
  }

  // Check resizing (set an additional element and verify capacity increase)
  int new_value = 60;
  test(tc, "Resizing dynamic array",
       dynArray_set(&dynArray, 5, &new_value) == 0);
  test(tc, "Dynamic Array size after resize", dynArray.size == 6);
  test(tc, "Dynamic Array capacity after resize", dynArray.capacity > 5);

  // Check out-of-bounds access (getting element from index >= size)
  int out_of_bounds_fetched;
  test(tc, "Out of bounds get",
       dynArray_get(&dynArray, 6, &out_of_bounds_fetched) != 0);

  // Check setting element at an out-of-bounds index
  test(tc, "Capacity exceeds SIZE_MAX set",
       dynArray_set(&dynArray, INT_MAX, &new_value) != 0);

  // Free dynamic array
  dynArray_free(&dynArray);
  test(tc, "Dynamic Array free",
       dynArray.data == NULL && dynArray.capacity == 0 && dynArray.size == 0);

  if (tc->failures > 0) {
    printf("\n%d/%d tests failed!\n", tc->failures, tc->count);
  } else {
    printf("\nAll tests passed!\n");
  }
}

int main() {
  TestContext tc = create_context();
  test_dynArray_operations(&tc);
  return 0;
}
