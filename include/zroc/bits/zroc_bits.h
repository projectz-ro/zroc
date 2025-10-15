#pragma once

#include "zroc/base_types.h"

static inline usize bit(u8 n) { return ((usize)1) << n; };
static inline void set_bit(usize *v, usize b) { *v |= b; };
static inline void clear_bit(usize *v, usize b) { *v &= ~b; };
static inline void toggle_bit(usize *v, usize b) { *v ^= b; };
static inline boolean check_bit(usize v, usize b) { return (v & b) != 0; };
