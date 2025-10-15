#include "zroc/memory/zroc_memory.h"
#include "zroc/error/zroc_error.h"
#include <stdint.h>
#include <stdlib.h>
#include <zroc/log/zroc_log.h>

void *zroc_malloc(size_t size) {
  if ((size < 1) || (size >= SIZE_MAX)) {
    zroc_err_set(ZROC_ERR_INVALID_ARG, "'size' must be > 0 < SIZE_MAX");
    return NULL;
  }
  void *ptr = malloc(size);
  if (!ptr) {
    zroc_err_set(ZROC_ERR_ALLOC_FAILED, "failed to allocate memory");
    return NULL;
  }
  return ptr;
}

void *zroc_calloc(size_t count, size_t size) {
  if ((size * count <= 0) || (size * count >= SIZE_MAX)) {
    zroc_err_set(ZROC_ERR_INVALID_ARG,
                 "'size' * `count` must be > 0 < SIZE_MAX");
    return NULL;
  }
  void *ptr = calloc(count, size);
  if (!ptr) {
    zroc_err_set(ZROC_ERR_ALLOC_FAILED, "failed to allocate memory");
    return NULL;
  }
  return ptr;
}

void *zroc_realloc(void *ptr, size_t size) {
  if (size < 1 || size >= SIZE_MAX) {
    zroc_err_set(ZROC_ERR_INVALID_ARG, "'size' must be > 0 < SIZE_MAX");
    return NULL;
  }
  void *tmp = realloc(ptr, size);
  if (!tmp) {
    zroc_err_set(ZROC_ERR_ALLOC_FAILED, "failed to allocate memory");
    return NULL;
  }
  return tmp;
}

void zroc_free(void *ptr) {
  if (ptr) {
    free(ptr);
  }
}
