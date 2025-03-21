#ifndef ZROC_ARRAY
#define ZROC_ARRAY
#include <stdio.h>

typedef struct {
  void *data;
  size_t size;
  size_t capacity;
  size_t element_size;
} Zroc_Array;

Zroc_Array *array_new(size_t element_size, size_t capacity);
void array_set(Zroc_Array *arr, int index, void *value);
void *array_get(Zroc_Array *arr, int index);
void array_free(Zroc_Array *arr);

#endif
