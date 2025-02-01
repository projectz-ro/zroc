#ifndef ZROC_TESTING_H
#define ZROC_TESTING_H

#include <stdio.h>

typedef struct {
  int count;
  int failures;
  FILE *og_stderr;
} TestContext;

int test(TestContext *tc, const char *test_name, int condition);

TestContext create_context();
void suppress_stderr(TestContext *tc);
void restore_stderr(TestContext *tc);

#endif
