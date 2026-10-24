#ifndef _global_h_
#define _global_h_

/* Trimmed copy of zeldaret/tp include/global.h: only what the MSL_C sources use. */

#define VERSION_GCN_USA          0
#define VERSION_GCN_PAL          1
#define VERSION_GCN_JPN          2
#define VERSION_WII_USA_R0       3
#define VERSION_WII_PAL_KIOSK    9
#define VERSION_SHIELD           10
#define VERSION_SHIELD_DEBUG     12

#ifndef VERSION
#define VERSION VERSION_GCN_USA
#endif

#define PLATFORM_GCN    (VERSION >= VERSION_GCN_USA && VERSION <= VERSION_GCN_JPN)
#define PLATFORM_WII    (VERSION >= VERSION_WII_USA_R0 && VERSION <= VERSION_WII_PAL_KIOSK)
#define PLATFORM_SHIELD (VERSION >= VERSION_SHIELD && VERSION <= VERSION_SHIELD_DEBUG)

#ifndef DEBUG
#define DEBUG 0
#endif

#define MSL_INLINE inline

#define ARRAY_SIZE(o) (s32)(sizeof(o) / sizeof(o[0]))
#define ARRAY_SIZEU(o) (sizeof(o) / sizeof(o[0]))

#define UNUSED(x) ((void)(x))

#ifdef __MWERKS__
#define ASM asm
#else
#define ASM
#endif

#endif
