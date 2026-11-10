#ifndef GAME_TYPES_AT_ADDRESS_H
#define GAME_TYPES_AT_ADDRESS_H

/*
 * AT_ADDRESS(addr): Metrowerks' `T name : 0xADDR;` (a variable placed at an
 * absolute address, e.g. the GX write-gather pipe at 0xCC008000). Other
 * compilers do not have the syntax; there the variable is an ordinary
 * definition and the PC port supplies the storage. Same macro as in
 * include/dolphin/types.h, for game files that do not include the SDK headers.
 */
#ifndef AT_ADDRESS
#if defined(__MWERKS__)
#define AT_ADDRESS(addr) : (addr)
#else
#define AT_ADDRESS(addr)
#endif
#endif

#endif
