#include "../../include/ds/zroc_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int array_new(size_t element_size, size_t capacity, Zroc_Array *out) {
  if (!out) {
    fputs("Error: Null \"out\".\n", stderr);
    return -1;
  }
  out->data = malloc(element_size * capacity);
  if (out->data == NULL) {
    fputs("Error: Memory allocation for new_array failed.\n", stderr);
    return -1;
  }

  out->size = 0;
  out->capacity = capacity;
  out->element_size = element_size;

  memset(out->data, 0, element_size * capacity);

  return 0;
}

int array_get(Zroc_Array *arr, int index, void *out) {
  if (!out) {
    fputs("Error: Null \"out\".\n", stderr);
    return -1;
  }
  if (index >= arr->size || index < 0) {
    fprintf(stderr,
            "Error: Index out of bounds for array_get. Index: %d, Size: %zu\n",
            index, arr->size);
    return -1;
  }
  memcpy(out, (char *)(arr->data + arr->element_size * index),
         arr->element_size);

  return 0;
}

int array_set(Zroc_Array *arr, int index, void *value) {
  if (!value) {
    fputs("Error: Null \"value\".\n", stderr);
    return -1;
  }
  if (index >= arr->capacity || index < 0) {
    fprintf(
        stderr,
        "Error: Index out of bounds for array_set. Index: %d, capacity: %zu\n",
        index, arr->capacity);
    return -1;
  }
  void *dest = (char *)(arr->data + arr->element_size * index);
  memcpy(dest, value, arr->element_size);
  arr->size++;

  return 0;
}

void array_free(Zroc_Array *arr) {
  if (!arr || !arr->data) {
    fputs("Error: Null pointer encountered in array_free.\n", stderr);
    return;
  }
  free(arr->data);
  arr->element_size = 0;
  arr->size = 0;
  arr->capacity = 0;
  arr->data = NULL;
}
