#ifndef ZROC_LIST
#define ZROC_LIST
#include "zroc_dynArray.h"
#include <stdlib.h>

typedef struct Node {
  void *data;
  Node *previous;
  Node *next;
} Node;

typedef struct {
  size_t size;
  size_t capacity;
  size_t element_size;
} List;

#endif
