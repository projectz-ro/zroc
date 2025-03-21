#include "include/ds/zroc_sparse_set.h"
#include "include/ds/zroc_dynArray.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Zroc_Sparse_Set *sparse_set_new(size_t capacity, size_t element_size) {
  errno = 0;
  Zroc_Sparse_Set *new_sparse =
      (Zroc_Sparse_Set *)malloc(sizeof(Zroc_Sparse_Set));
  if (new_sparse == NULL) {
    errno = ENOMEM;
    return NULL;
  }
  new_sparse->sparse = dynArray_new(sizeof(int), capacity);
  if (new_sparse->sparse == NULL) {
    free(new_sparse);
    return NULL;
  }
  new_sparse->dense = dynArray_new(element_size, 1);
  if (new_sparse->dense == NULL) {
    dynArray_free(new_sparse->sparse);
    free(new_sparse);
    return NULL;
  }
  new_sparse->indices = dynArray_new(sizeof(int), 1);
  if (new_sparse->indices == NULL) {
    dynArray_free(new_sparse->dense);
    dynArray_free(new_sparse->sparse);
    free(new_sparse);
    return NULL;
  }
  return new_sparse;
}

void sparse_set_add(Zroc_Sparse_Set *sparse_set, int index, void *value) {
  errno = 0;
  if (sparse_set == NULL || value == NULL || index < 0) {
    errno = EINVAL;
    return;
  }
  int dense_index = sparse_set->dense->size;
  dynArray_set(sparse_set->dense, dense_index, value);
  if (errno != 0) {
    return;
  }
  dynArray_set(sparse_set->indices, dense_index, &index);
  if (errno != 0) {
    return;
  }
  dynArray_set(sparse_set->sparse, index, &dense_index);
  if (errno != 0) {
    return;
  }
}

void sparse_set_remove(Zroc_Sparse_Set *sparse_set, int index) {
  errno = 0;
  if (sparse_set == NULL || index < 0) {
    errno = EINVAL;
    return;
  }

  // Get the dense index for this sparse index
  int *dense_index_ptr = dynArray_get(sparse_set->sparse, index);
  if (dense_index_ptr == NULL) {
    errno = ENOENT;
    return;
  }
  int dense_index = *dense_index_ptr;

  // Get the last element's index
  int last_dense_index = sparse_set->dense->size - 1;
  if (dense_index != last_dense_index) {
    // Move the last element to the removed element's position
    void *last_element = dynArray_get(sparse_set->dense, last_dense_index);
    if (last_element == NULL) {
      return;
    }

    // Copy the last element to the removed position
    void *dest = dynArray_get(sparse_set->dense, dense_index);
    if (dest == NULL) {
      return;
    }
    memcpy(dest, last_element, sparse_set->dense->element_size);

    // Update the indices
    int *last_sparse_index_ptr =
        dynArray_get(sparse_set->indices, last_dense_index);
    if (last_sparse_index_ptr == NULL) {
      return;
    }
    int last_sparse_index = *last_sparse_index_ptr;

    // Update the sparse array to point to the new dense index
    dynArray_set(sparse_set->sparse, last_sparse_index, &dense_index);
    if (errno != 0) {
      return;
    }

    // Update the indices array
    dynArray_set(sparse_set->indices, dense_index, &last_sparse_index);
    if (errno != 0) {
      return;
    }
  }

  // Reduce the size of the dense and indices arrays
  sparse_set->dense->size--;
  sparse_set->indices->size--;
}

void *sparse_set_get(Zroc_Sparse_Set *sparse_set, int index) {
  errno = 0;
  if (sparse_set == NULL || index < 0) {
    errno = EINVAL;
    return NULL;
  }

  // Get the dense index for this sparse index
  int *dense_index_ptr = dynArray_get(sparse_set->sparse, index);
  if (dense_index_ptr == NULL) {
    errno = ENOENT;
    return NULL;
  }

  // Get the actual element
  return dynArray_get(sparse_set->dense, *dense_index_ptr);
}

void sparse_set_free(Zroc_Sparse_Set *sparse_set) {
  if (sparse_set == NULL) {
    return;
  }

  if (sparse_set->sparse != NULL) {
    dynArray_free(sparse_set->sparse);
  }

  if (sparse_set->dense != NULL) {
    dynArray_free(sparse_set->dense);
  }

  if (sparse_set->indices != NULL) {
    dynArray_free(sparse_set->indices);
  }

  free(sparse_set);
}
