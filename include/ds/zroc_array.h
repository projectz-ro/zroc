#ifndef ZROC_ARRAY_H
#define ZROC_ARRAY_H
#include <stdio.h>

typedef struct {
  void *data;
  size_t size;
  size_t capacity;
  size_t element_size;
} Zroc_Array;

int new_array(size_t element_size, size_t capacity, Zroc_Array *out);
int array_get(Zroc_Array *arr, int index, void *out);
int array_set(Zroc_Array *arr, int index, void *value);
void array_free(Zroc_Array *arr);

#endif
