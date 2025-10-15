/**
 * @file zroc_log.h
 * @brief Logging utilities for ZroC.
 *
 * Provides a simple logging API with log levels and optional prefixes.
 */

#pragma once

#include <stdio.h>

/**
 * @enum ZrocLogLevel
 * @brief Log levels supported by ZroC.
 */
typedef enum ZrocLogLevel {
  ZROC_LOG_DEBUG, /**< Debug-level messages. */
  ZROC_LOG_INFO,  /**< Informational messages. */
  ZROC_LOG_WARN,  /**< Warning messages. */
  ZROC_LOG_ERROR  /**< Error messages. */
} ZrocLogLevel;

/**
 * @struct ZrocLogger
 * @brief Represents a logger object.
 *
 * A logger controls where messages are written and which level
 * of messages are actually output.
 */
typedef struct ZrocLogger {
  int level;          /**< Minimum log level to output. */
  FILE *output;       /**< Output stream (e.g., stderr, file). */
  const char *prefix; /**< Optional prefix string for all messages. */
} ZrocLogger;

/**
 * @brief Create a new logger.
 *
 * @param output The output stream (e.g., stderr or a file pointer).
 * @param level Minimum log level to output.
 * @param prefix Optional prefix to prepend to every message (can be NULL).
 * @return Pointer to a newly allocated ZrocLogger, or NULL on failure.
 *
 * @note The returned logger must be freed with zroc_logger_free().
 */
ZrocLogger *zroc_logger_create(FILE *output, int level, const char *prefix);

/**
 * @brief Free a logger.
 *
 * @param logger Pointer to the logger to free.
 */
void zroc_logger_free(ZrocLogger *logger);

/**
 * @brief Log a formatted message.
 *
 * @param logger Pointer to the logger to use.
 * @param lvl Log level of this message.
 * @param fmt Format string (printf-style).
 * @param ... Format arguments.
 *
 * @note Messages with a level lower than the logger's `level` will be ignored.
 */
void zroc_log(ZrocLogger *logger, ZrocLogLevel lvl, const char *fmt, ...);
