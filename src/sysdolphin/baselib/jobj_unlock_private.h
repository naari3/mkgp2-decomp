/* Assertion strings remain owned by the original contiguous fallback pools. */
#ifndef MKGP2_JOBJ_UNLOCK_PRIVATE_H
#define MKGP2_JOBJ_UNLOCK_PRIVATE_H
#include "debug.h"
extern char lbl_804FCB88[9];
extern char lbl_804FCB94[39];
extern char lbl_804FCBBC[452];
/* The object header's assertions share the original object.h strings. */
#define __assert(file, line, msg) __assert(lbl_804FCB88, line, (line) == 93 ? lbl_804FCB94 : lbl_804FCBBC)
#include "object.h"
#undef __assert
extern char lbl_806D0DA0[7];
extern char lbl_806D0DA8[5];
extern char lbl_806D0DB0[7];
extern char lbl_806D0DB8[3];
extern char lbl_804FC9A8[0x3D8];
/* Bind the header assertions before including its inline setters. */
#undef HSD_ASSERT
#define HSD_ASSERT(line, cond) ((cond) ? (void)0 : __assert(lbl_806D0DA0, line, sizeof(#cond) == 5 ? lbl_806D0DA8 : (((line) == 677 || (line) == 697 || (line) == 717) ? lbl_804FC9A8 + 0x80 : #cond)))
/* jobj_ref_INC spells out its object.h assertion. */
#define __assert(file, line, msg) __assert((line) == 93 ? lbl_804FCB88 : (file), line, (line) == 93 ? lbl_804FCB94 : (msg))
#include "jobj.h"
#undef __assert
#undef HSD_ASSERT
#define HSD_ASSERT(line, cond) ((cond) ? (void)0 : __assert(lbl_806D0DB0, line, #cond))
#endif
