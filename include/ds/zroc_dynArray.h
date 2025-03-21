#ifndef ZROC_DYNARRAY
#define ZROC_DYNARRAY
#include <stdio.h>

typedef struct {
  void *data;
  size_t size;
  size_t capacity;
  size_t element_size;
} Zroc_DynArray;

Zroc_DynArray *dynArray_new(size_t element_size, size_t capacity);
void dynArray_expand(Zroc_DynArray *arr);
void *dynArray_get(Zroc_DynArray *arr, int index);
void dynArray_set(Zroc_DynArray *arr, int index, void *value);
void dynArray_free(Zroc_DynArray *arr);

#endif
