#ifndef GAME_TYPES_SHARED_DATA_H
#define GAME_TYPES_SHARED_DATA_H

/* Storage class of a data definition that one unit owns and other units reach
 * by its symbols.txt name.
 *
 * Under MWCC the definition has to stay exactly as it is (a `static`, or a
 * C++ `const` with internal linkage): data order and pooling depend on it,
 * and the link still resolves the other units' references, either because
 * the build renames the symbol after compiling (tools/extab_user_renames.json)
 * or because the original object is linked. Any other compiler needs one
 * external definition under the shared name. tools/alias_census.py lists the
 * pairs.
 *
 *   SHARED_STATIC const T x[] = {...};   static here, external elsewhere
 *                                        (definitions with an initializer)
 *   SHARED_BSS T x;                      the same without an initializer
 *   SHARED_EXTERN const T x = ...;       nothing here, `extern` elsewhere
 *                                        (C++ const that is not static)
 *
 * When the source name differs from the shared one, the unit also has
 *   #ifndef __MWERKS__
 *   #define localName Shared_Name_80xxxxxx
 *   #endif
 * in front of the definition.
 */
#ifdef __MWERKS__
#define SHARED_STATIC static
#define SHARED_BSS static
#define SHARED_EXTERN
#else
#define SHARED_STATIC extern
#define SHARED_BSS
#define SHARED_EXTERN extern
#endif

#endif
