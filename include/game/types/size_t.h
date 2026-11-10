#ifndef GAME_TYPES_SIZE_T_H
#define GAME_TYPES_SIZE_T_H
#include "game/types/size_t.h"

/*
 * size_t for declarations of `operator new` / `operator new[]`.
 *
 * C++ requires the first parameter of an allocation function to be exactly
 * size_t. Metrowerks' size_t is `unsigned long` (mangled `Ul`, as in
 * __nw__FUl), so spelling the parameter `size_t` gives the same objects, and
 * the same declaration is accepted by compilers whose size_t is another type
 * (clang/MSVC on 64-bit targets), which reject `operator new(size_t)`.
 */
#ifdef __MWERKS__
typedef unsigned long size_t;
#else
#include <stddef.h>
#endif

#endif
