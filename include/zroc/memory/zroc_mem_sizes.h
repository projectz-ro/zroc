#pragma once
#include "zroc/base_types.h"

static inline usize KiB(usize x) { return x * 1024ULL; }
static inline usize MiB(usize x) {
  return (x <= (SIZE_MAX / (1024ULL * 1024ULL))) ? x * 1024ULL * 1024ULL
                                                 : 0;
}
static inline usize GiB(usize x) {
  return (x <= (SIZE_MAX / (1024ULL * 1024ULL * 1024ULL)))
             ? x * 1024ULL * 1024ULL * 1024ULL
             : 0;
}
