#include "zroc/error/zroc_error.h"
#include "zroc/memory/zroc_memory.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <zroc/log/zroc_log.h>

const ZrocErr ZROC_ERRORS[] = {
    {.code = ZROC_OK, .message = ""},
    {.code = ZROC_ERR_UNKNOWN, .message = "Unknown error"},
    {.code = ZROC_ERR_INVALID_ARG, .message = "Invalid argument"},
    {.code = ZROC_ERR_OUT_OF_MEMORY, .message = "Out of memory"},
    {.code = ZROC_ERR_ALLOC_FAILED, .message = "Allocation failed"},
    {.code = ZROC_ERR_IO, .message = "I/O error"},
    {.code = ZROC_ERR_NOT_FOUND, .message = "Resource not found"},
    {.code = ZROC_ERR_ALREADY_EXISTS, .message = "Resource already exists"},
    {.code = ZROC_ERR_UNSUPPORTED, .message = "Operation not supported"},
    {.code = ZROC_ERR_TIMEOUT, .message = "Operation timed out"},
    {.code = ZROC_ERR_STATE, .message = "Invalid state"},
    {.code = ZROC_ERR_PERMISSION, .message = "Permission denied"},
    {.code = ZROC_ERR_OUT_OF_RANGE, .message = "Value or index out of range"},
    {.code = ZROC_ERR_DIV_BY_ZERO, .message = "Division by zero"},
    {.code = ZROC_ERR_OVERFLOW, .message = "Numeric overflow"},
    {.code = ZROC_ERR_NULL_POINTER, .message = "Null pointer"},
    {.code = ZROC_ERR_FORMAT, .message = "Format/parsing error"},
    {.code = ZROC_ERR_UNINITIALIZED, .message = "Uninitialized object"},
    {.code = ZROC_ERR_LIMIT_EXCEEDED, .message = "Limit exceeded"},
};

static pthread_key_t error_key;
static pthread_once_t error_key_once = PTHREAD_ONCE_INIT;
static void make_error_key() { pthread_key_create(&error_key, free); }

ZrocErr *zroc_err_get(void) {
  pthread_once(&error_key_once, make_error_key);
  ZrocErr *err = pthread_getspecific(error_key);
  if (!err) {
    err = zroc_calloc(1, sizeof(ZrocErr));
    err->code = ZROC_OK;
    err->message = zroc_calloc(ERR_MSG_MAX_SIZE, sizeof(char));
    pthread_setspecific(error_key, err);
  }
  return err;
}

void zroc_err_set(ZrocErrCode code, const char *msg) {
  if (!msg && (code < ZROC_ERR_CUSTOM_BASE)) {
    msg = ZROC_ERRORS[code].message;
  }
  ZrocErr *err = zroc_err_get();
  err->code = code;
  snprintf(err->message, ERR_MSG_MAX_SIZE, "%s", msg);
}
