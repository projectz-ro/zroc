#ifndef ZROC_DYNARRAY_H
#define ZROC_DYNARRAY_H
#include <stdio.h>

typedef struct {
  void *data;
  size_t size;
  size_t capacity;
  size_t element_size;
} Zroc_DynArray;

int dynArray_new(size_t element_size, size_t capacity, Zroc_DynArray *out);
int dynArray_expand(Zroc_DynArray *arr);
int dynArray_get(Zroc_DynArray *arr, int index, void *out);
int dynArray_set(Zroc_DynArray *arr, int index, void *value);
void dynArray_free(Zroc_DynArray *arr);

#endif
