#include "include/ds/zroc_dynArray.h"
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Zroc_DynArray *dynArray_new(size_t element_size, size_t capacity) {
  errno = 0;
  if (element_size == 0 || capacity == 0) {
    errno = EINVAL;
    return NULL;
  }
  if (element_size * capacity > SIZE_MAX) {
    errno = EOVERFLOW;
    return NULL;
  }
  Zroc_DynArray *new_array = (Zroc_DynArray *)malloc(sizeof(Zroc_DynArray));
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

void *dynArray_get(Zroc_DynArray *arr, int index) {
  errno = 0;
  if (arr == NULL) {
    errno = EINVAL;
    return NULL;
  }
  if (index < 0 || index >= (int)arr->size) {
    errno = ERANGE;
    return NULL;
  }
  return (char *)arr->data + (arr->element_size * index);
}

void dynArray_set(Zroc_DynArray *arr, int index, void *value) {
  errno = 0;
  if (arr == NULL || value == NULL) {
    errno = EINVAL;
    return;
  }
  if (index < 0) {
    errno = ERANGE;
    return;
  }
  if (index >= (int)arr->size) {
    arr->size = index + 1;
  }
  if (arr->size > arr->capacity) {
    dynArray_expand(arr);
    if (errno != 0) {
      return;
    }
  }
  void *dest = (char *)arr->data + (arr->element_size * index);
  memcpy(dest, value, arr->element_size);
}

void dynArray_expand(Zroc_DynArray *arr) {
  errno = 0;
  if (arr == NULL) {
    errno = EINVAL;
    return;
  }
  if (arr->capacity > SIZE_MAX / 2) {
    errno = EOVERFLOW;
    return;
  }
  size_t new_capacity = arr->capacity * 2;
  void *temp = realloc(arr->data, arr->element_size * new_capacity);
  if (temp == NULL) {
    errno = ENOMEM;
    return;
  }
  arr->data = temp;
  arr->capacity = new_capacity;
}

void dynArray_free(Zroc_DynArray *arr) {
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
