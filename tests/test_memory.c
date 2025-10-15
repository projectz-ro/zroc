#include "zroc/error/zroc_error.h"
#include "zroc/memory/zroc_memory.h"
#include <criterion/criterion.h>
#include <stdint.h>
#include <string.h>

Test(memory, malloc_valid_size) {
  size_t size = 64;
  void *ptr = zroc_malloc(size);
  cr_assert(ptr != NULL, "zroc_malloc should return non-NULL for valid size");
  zroc_free(ptr);
}

Test(memory, malloc_invalid_size_zero) {
  void *ptr = zroc_malloc(0);
  cr_assert(ptr == NULL, "zroc_malloc should return NULL for size 0");

  ZrocErr *err = zroc_err_get();
  cr_assert(err->code == ZROC_ERR_INVALID_ARG,
            "Error code should be ZROC_ERR_INVALID_ARG");
}

Test(memory, malloc_large_size) {
  void *ptr = zroc_malloc(SIZE_MAX);
  cr_assert(ptr == NULL, "zroc_malloc should fail for SIZE_MAX");

  ZrocErr *err = zroc_err_get();
  cr_assert(err->code == ZROC_ERR_INVALID_ARG,
            "Error code should be ZROC_ERR_INVALID_ARG");
}

Test(memory, calloc_zero_initialized) {
  size_t count = 10;
  size_t size = sizeof(int);

  int *arr = zroc_calloc(count, size);
  cr_assert(arr != NULL, "zroc_calloc should allocate memory");

  for (size_t i = 0; i < count; i++) {
    cr_assert(arr[i] == 0, "zroc_calloc should zero-initialize memory");
  }

  zroc_free(arr);
}

Test(memory, calloc_invalid_size) {
  void *ptr = zroc_calloc(0, 10);
  cr_assert(ptr == NULL, "zroc_calloc should return NULL for zero count");

  ZrocErr *err = zroc_err_get();
  cr_assert(err->code == ZROC_ERR_INVALID_ARG,
            "Error code should be ZROC_ERR_INVALID_ARG");
}

Test(memory, realloc_expand) {
  int *arr = zroc_calloc(5, sizeof(int));
  cr_assert(arr != NULL);

  int *new_arr = zroc_realloc(arr, 10 * sizeof(int));
  cr_assert(new_arr != NULL, "zroc_realloc should return valid pointer");

  for (int i = 0; i < 5; i++) {
    cr_assert(new_arr[i] == 0);
  }

  zroc_free(new_arr);
}

Test(memory, realloc_shrink) {
  int *arr = zroc_calloc(10, sizeof(int));
  cr_assert(arr != NULL);

  int *new_arr = zroc_realloc(arr, 5 * sizeof(int));
  cr_assert(new_arr != NULL,
            "zroc_realloc should return valid pointer when shrinking");

  zroc_free(new_arr);
}

Test(memory, realloc_invalid_size) {
  int *arr = zroc_calloc(5, sizeof(int));
  cr_assert(arr != NULL);

  int *new_arr = zroc_realloc(arr, SIZE_MAX);
  cr_assert(new_arr == NULL,
            "zroc_realloc should return NULL for invalid size");

  ZrocErr *err = zroc_err_get();
  cr_assert(err->code == ZROC_ERR_INVALID_ARG,
            "Error code should be ZROC_ERR_INVALID_ARG");

  zroc_free(arr);
}

Test(memory, free_null) {
  zroc_free(NULL);
  cr_assert(true, "zroc_free(NULL) should not crash");
}
