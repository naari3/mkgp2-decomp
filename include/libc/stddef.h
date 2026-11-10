#ifndef _STDDEF_H_
#define _STDDEF_H_

#define offsetof(type, member)	((size_t) &(((type *) 0)->member))

/* Metrowerks' size_t is unsigned long (operator new mangles as __nw__FUl). */
#if defined(__MWERKS__) || !defined(__SIZE_TYPE__)
typedef unsigned long size_t;
#else
typedef __SIZE_TYPE__ size_t;
#endif

#ifndef NULL
#define NULL 0L
#endif

#endif
