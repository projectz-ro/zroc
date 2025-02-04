#include "../../include/ds/zroc_dynArray.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dynArray_new(size_t element_size, size_t capacity, Zroc_DynArray *out) {
  if (!out) {
    fputs("Error: Null \"out\" pointer passed to new_dynArray.\n", stderr);
    return -1;
  }
  out->data = malloc(element_size * capacity);
  if (out->data == NULL) {
    fprintf(stderr, "Error: Memory allocation for %p in new_dynArray failed.\n",
            (void *)out);
    return -1;
  }

  out->size = 0;
  out->capacity = capacity;
  out->element_size = element_size;

  memset(out->data, 0, element_size * capacity);

  return 0;
}

int dynArray_get(Zroc_DynArray *arr, int index, void *out) {
  if (!out) {
    fputs("Error: Null \"out\" pointer passed to dynArray_get.\n", stderr);
    return -1;
  }
  if (index < 0 || index >= (int)arr->size) {
    fprintf(stderr, "Error: Index %d out of bounds for dynArray_get.\n", index);
    return -1;
  }
  memcpy(out, (char *)arr->data + (arr->element_size * index),
         arr->element_size);

  return 0;
}

int dynArray_set(Zroc_DynArray *arr, int index, void *value) {
  if (!value) {
    fputs("Error: Null pointer for \"value\".\n", stderr);
    return -1;
  }
  if (index < 0) {
    fprintf(stderr, "Error: Index %d out of bounds for dynArray_set.\n", index);
    return -1;
  }
  if (index >= (int)arr->size) {
    arr->size = index + 1;
  }
  if (arr->size >= arr->capacity) {
    arr->capacity = arr->size;
    int error = dynArray_expand(arr);
    if (error) {
      fputs("Error: Array expansion failed on dynArray_set.\n", stderr);
      return -1;
    }
  }

  void *dest = (char *)arr->data + (arr->element_size * index);
  memcpy(dest, value, arr->element_size);

  return 0;
}

int dynArray_expand(Zroc_DynArray *arr) {
  if (arr->capacity > SIZE_MAX / 2) {
    fputs("Error: Stack capacity overflow in dynArray_expand.\n", stderr);
    return -1;
  }

  arr->capacity *= 2;
  void *temp = realloc(arr->data, arr->element_size * arr->capacity);
  if (!temp) {
    fputs(
        "Error: Memory reallocation for expansion failed in dynArray_expand.\n",
        stderr);
    return -1;
  }
  arr->data = temp;
  return 0;
}

void dynArray_free(Zroc_DynArray *arr) {
  if (!arr || !arr->data)
    return;
  free(arr->data);
  arr->element_size = 0;
  arr->size = 0;
  arr->capacity = 0;
  arr->data = NULL;
}
