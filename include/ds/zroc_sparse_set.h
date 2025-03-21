#ifndef ZROC_SPARSE_SET
#define ZROC_SPARSE_SET
#include "zroc_dynArray.h"

#define SPARSE_EMPTY_SPACE -1

typedef struct {
  Zroc_DynArray *sparse;
  Zroc_DynArray *dense;
  Zroc_DynArray *indices;
} Zroc_Sparse_Set;

Zroc_Sparse_Set *sparse_set_new(size_t capacity, size_t element_size);
void sparse_set_add(Zroc_Sparse_Set *sparse_set, int index, void *value);
void sparse_set_remove(Zroc_Sparse_Set *sparse_set, int index);
void *sparse_set_get(Zroc_Sparse_Set *sparse_set, int index);
void sparse_set_free(Zroc_Sparse_Set *sparse_set);

#endif
