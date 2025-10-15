/**
 * @file zroc_memory.h
 * @brief Memory allocation wrappers with error checking.
 *
 * Provides safe malloc, calloc, realloc, and free functions
 * that log errors internally on failure.
 */

#pragma once

#include "zroc/error/zroc_error.h"
#include "zroc/log/zroc_log.h"
#include <stddef.h>

#if ZROC_MEM_TRACK
#define zroc_malloc(size) zroc_malloc_track(size, __FILE__, __LINE__)
#define zroc_calloc(count, size)                                               \
  zroc_calloc_track(count, size, __FILE__, __LINE__)
#define zroc_realloc(ptr, size)                                                \
  zroc_realloc_track(ptr, size, __FILE__, __LINE__)
#define zroc_free(ptr) zroc_free_track(ptr, __FILE__, __LINE__)
#endif

/**
 * @brief Allocate memory safely.
 *
 * @param size Number of bytes to allocate.
 * @return Pointer to allocated memory, or NULL on failure.
 *
 * @note Logs an error if allocation fails or if size is invalid.
 */
void *zroc_malloc(size_t size);

/**
 * @brief Allocate zero-initialized memory safely.
 *
 * @param count Number of elements.
 * @param size Size of each element.
 * @return Pointer to allocated memory, or NULL on failure.
 *
 * @note Logs an error if allocation fails or if total size is invalid.
 */
void *zroc_calloc(size_t count, size_t size);

/**
 * @brief Resize previously allocated memory.
 *
 * @param ptr Pointer to previously allocated memory.
 * @param size New size in bytes.
 * @return Pointer to resized memory, or NULL on failure.
 *
 * @note Original memory is not freed if realloc fails.
 * @note Logs an error if allocation fails or if size is invalid.
 */
void *zroc_realloc(void *ptr, size_t size);

/**
 * @brief Free memory safely.
 *
 * @param ptr Pointer to memory to free. Can be NULL.
 */
void zroc_free(void *ptr);
