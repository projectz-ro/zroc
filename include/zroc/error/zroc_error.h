/**
 * @file zroc_error.h
 * @brief Thread-local error handling system for Zroc.
 */

#pragma once

/**
 * @brief Maximum length of an error message.
 */
#define ERR_MSG_MAX_SIZE 256

/**
 * @brief Codes representing different types of errors.
 *
 * Extend by creating a new enum such as:
 *
 * typedef struct MyErrCode{
 *   MY_ERR_INSERT = ZROC_ERR_CUSTOM_BASE + 1,
 *   MY_ERR_DELETE,
 *   MY_ERR_LOOKUP,
 *   ...
 * }MyErrCode;
 *
 */
typedef enum {
  ZROC_OK = 0,            /**< No error */
  ZROC_ERR_UNKNOWN,       /**< Unknown/unclassified error */
  ZROC_ERR_INVALID_ARG,   /**< Invalid argument passed to a function */
  ZROC_ERR_OUT_OF_MEMORY, /**< Memory allocation failed */
  ZROC_ERR_ALLOC_FAILED, /**< Specific allocation failure (e.g., object pool) */
  ZROC_ERR_IO,           /**< Generic I/O error */
  ZROC_ERR_NOT_FOUND,    /**< Requested resource not found */
  ZROC_ERR_ALREADY_EXISTS,    /**< Resource already exists */
  ZROC_ERR_UNSUPPORTED,       /**< Operation not supported */
  ZROC_ERR_TIMEOUT,           /**< Operation timed out */
  ZROC_ERR_STATE,             /**< Invalid state / precondition not met */
  ZROC_ERR_PERMISSION,        /**< Permission denied / access violation */
  ZROC_ERR_OUT_OF_RANGE,      /**< Value or index is out of allowed range */
  ZROC_ERR_DIV_BY_ZERO,       /**< Division or modulo by zero */
  ZROC_ERR_OVERFLOW,          /**< Numeric overflow */
  ZROC_ERR_NULL_POINTER,      /**< Null pointer encountered */
  ZROC_ERR_FORMAT,            /**< Parsing / serialization error */
  ZROC_ERR_UNINITIALIZED,     /**< Accessed uninitialized object */
  ZROC_ERR_LIMIT_EXCEEDED,    /**< Resource or container limit exceeded */
  ZROC_ERR_CUSTOM_BASE = 1000 /**< Base value for user-defined error codes */
} ZrocErrCode;

/**
 * @brief Thread-local error struct.
 */
typedef struct {
  ZrocErrCode code; /**< The error code. */
  char *message;    /**< Error message string. */
                    // TODO: Change to utf8 message once library is done
} ZrocErr;

/**
 * @brief Array of default errors with messages for each error code.
 *
 * Used as the source for default messages when none is provided.
 */
extern const ZrocErr ZROC_ERRORS[];

/**
 * @brief Get the thread-local error object.
 *
 * If the thread does not have an error object yet, one will be allocated and
 * initialized with code `ZROC_OK` and an empty message.
 *
 * @return Pointer to the thread-local ZrocErr object.
 */
ZrocErr *zroc_err_get(void);

/**
 * @brief Set the thread-local error.
 *
 * Updates the thread-local error code and message. If `msg` is `NULL`,
 * the default message for the given `code` from `ZROC_ERRORS` will be used.
 *
 * @param code The error code to set.
 * @param msg Optional error message. If NULL, the default is used.
 */
void zroc_err_set(ZrocErrCode code, const char *msg);
