#include "zroc_testing.h"

int test(TestContext *tc, const char *test_name, int passed) {
  tc->count++;
  if (!passed) {
    tc->failures++;
    printf("\033[31m[FAIL]\033[0m %s\n", test_name);
    return 1;
  }
  printf("\033[32m[PASS]\033[0m %s\n", test_name);
  return 0;
}

TestContext create_context() {
  FILE *file;
  TestContext t = {0, 0, file};
  return t;
}

void suppress_stderr(TestContext *tc) {
  tc->og_stderr = stderr;
  stderr = fopen("/dev/null", "w");
}

void restore_stderr(TestContext *tc) { stderr = tc->og_stderr; }
