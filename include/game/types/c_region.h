#ifndef GAME_TYPES_C_REGION_H
#define GAME_TYPES_C_REGION_H

/*
 * C_REGION_BEGIN / C_REGION_END mark the parts of a source file that
 * Metrowerks compiles as C: a .c file up to `#pragma cplusplus on`, and
 * whatever follows `#pragma cplusplus off` / `reset`.
 *
 * Other compilers have no such pragma and compile a file that contains C++
 * as C++ from the first line. There the markers become `extern "C" { ... }`,
 * so the functions and data of the C parts keep the unmangled names that the
 * rest of the game refers to, and a C declaration agrees with a later
 * `extern "C"` definition of the same function. Under Metrowerks they expand
 * to nothing. Placed by tools/c_regions.py.
 */
#if defined(__cplusplus) && !defined(__MWERKS__)
#define C_REGION_BEGIN extern "C" {
#define C_REGION_END }
#else
#define C_REGION_BEGIN
#define C_REGION_END
#endif

#endif
