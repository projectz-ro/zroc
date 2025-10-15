/**
 * @file zroc_flags.h
 * @brief Compile-time configuration flags for ZroC libraries.
 *
 * This header defines all configurable macros for enabling debug features,
 * memory tracking, logging verbosity, and other optional behaviors.
 * Users can override these by defining the macros via compiler flags
 * (e.g., `-DZROC_DEBUG=1`) or before including this header.
 */

#pragma once

/// @def ZROC_DEBUG
/// Enable general debug features, assertions, and logging.
/// 0 = disabled, 1 = enabled.
#ifndef ZROC_DEBUG
#define ZROC_DEBUG 0
#endif

/// @def ZROC_LOG_V
/// Enable verbose logging for detailed runtime information.
/// 0 = disabled, 1 = enabled.
#ifndef ZROC_LOG_V
#define ZROC_LOG_V 0
#endif

/// @def ZROC_MEM_TRACK
/// Track memory allocations and deallocations to detect leaks.
/// 0 = disabled, 1 = enabled.
#ifndef ZROC_MEM_TRACK
#define ZROC_MEM_TRACK 0
#endif

/// @def ZROC_MEM_FILL
/// Fill allocated and freed memory with known patterns to detect
/// uninitialized reads or use-after-free bugs.
/// 0 = disabled, 1 = enabled.
/// TODO: Implement this functionality in memory wrappers.
#ifndef ZROC_MEM_FILL
#define ZROC_MEM_FILL 0
#endif
