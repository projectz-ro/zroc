#include "include/ds/zroc_array.h"
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Zroc_Array *array_new(size_t element_size, size_t capacity) {
  errno = 0;
  if (element_size == 0 || capacity == 0) {
    errno = EINVAL;
    return NULL;
  }
  if (element_size * capacity > SIZE_MAX) {
    errno = EOVERFLOW;
    return NULL;
  }
  Zroc_Array *new_array = (Zroc_Array *)malloc(sizeof(Zroc_Array));
  if (new_array == NULL) {
    errno = ENOMEM;
    return NULL;
  }
  new_array->data = malloc(element_size * capacity);
  if (new_array->data == NULL) {
    errno = ENOMEM;
    free(new_array);
    return NULL;
  }
  new_array->size = 0;
  new_array->capacity = capacity;
  new_array->element_size = element_size;
  return new_array;
}

void *array_get(Zroc_Array *arr, int index) {
  errno = 0;
  if (arr == NULL) {
    errno = EINVAL;
    return NULL;
  }
  if (index >= (int)arr->size || index < 0) {
    errno = ERANGE;
    return NULL;
  }
  return (char *)arr->data + arr->element_size * index;
}

void array_set(Zroc_Array *arr, int index, void *value) {
  errno = 0;
  if (arr == NULL || value == NULL) {
    errno = EINVAL;
    return;
  }
  if (index >= (int)arr->capacity || index < 0) {
    errno = ERANGE;
    return;
  }
  void *dest = (char *)arr->data + arr->element_size * index;
  memcpy(dest, value, arr->element_size);
  if (index >= (int)arr->size) {
    arr->size = index + 1;
  }
}

void array_free(Zroc_Array *arr) {
  if (arr == NULL) {
    return;
  }
  if (arr->data != NULL) {
    free(arr->data);
    arr->data = NULL;
  }
  arr->element_size = 0;
  arr->size = 0;
  arr->capacity = 0;
  free(arr);
}
