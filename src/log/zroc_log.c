#include "zroc/log/zroc_log.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static ZrocLogger *internal_logger;

ZrocLogger *zroc_logger_create(FILE *output, int level, const char *prefix) {
  ZrocLogger *logger = malloc(sizeof *logger);
  logger->level = level;
  logger->output = output ? output : stderr;
  logger->prefix = prefix ? prefix : "";

  return logger;
}

void zroc_log(ZrocLogger *logger, ZrocLogLevel lvl, const char *fmt, ...) {
  if (!logger) {
    if (!internal_logger) {
      internal_logger = zroc_logger_create(stderr, ZROC_LOG_DEBUG, "ZroC");
      logger = internal_logger;
    }
  }
  if (lvl < logger->level)
    return;

  const char *lvl_str = "";
  switch (lvl) {
  case ZROC_LOG_DEBUG:
    lvl_str = "DEBUG";
    break;
  case ZROC_LOG_INFO:
    lvl_str = "INFO";
    break;
  case ZROC_LOG_WARN:
    lvl_str = "WARN";
    break;
  case ZROC_LOG_ERROR:
    lvl_str = "ERROR";
    break;
  }
  time_t now = time(NULL);
  struct tm *t = localtime(&now);

  fprintf(logger->output, "[%02d:%02d:%02d] [%s]", t->tm_hour, t->tm_min,
          t->tm_sec, lvl_str);
  if (logger->prefix)
    fprintf(logger->output, " [%s]", logger->prefix);

  fprintf(logger->output, " ");
  va_list args;
  va_start(args, fmt);
  vfprintf(logger->output, fmt, args);
  va_end(args);

  fprintf(logger->output, "\n");
  fflush(logger->output);
}

void zroc_logger_free(ZrocLogger *logger) {
  fclose(logger->output);
  free(logger);
}
