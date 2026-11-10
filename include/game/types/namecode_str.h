#ifndef GAME_TYPES_NAMECODE_STR_H
#define GAME_TYPES_NAMECODE_STR_H

/*
 * Byte-string functions applied to NameCode (unsigned short) strings.
 *
 * The card-name check keeps a name as 16-bit Shift-JIS codes and searches
 * and compares it with strstr / strcmp / strncmp / strcpy / strcat, i.e. as
 * bytes. On the console a code is stored high byte first, so those
 * functions see the Shift-JIS byte string, and a code below 0x100 (a
 * half-width character) starts with a zero byte and ends the string there.
 * A little-endian host stores the low byte first and gets other results for
 * such names.
 *
 * These names are the plain functions unless the build defines them first:
 * a port that wants the console's exact behaviour supplies versions that
 * work on the big-endian byte view (-DNAMECODE_STRSTR=... or a forced
 * include). The patterns compared with are NameCode arrays as well.
 * docs/notes/port_abi.md, "Card-name check".
 */
#ifndef NAMECODE_STRCMP
#define NAMECODE_STRCMP strcmp
#endif
#ifndef NAMECODE_STRNCMP
#define NAMECODE_STRNCMP strncmp
#endif
#ifndef NAMECODE_STRSTR
#define NAMECODE_STRSTR strstr
#endif
#ifndef NAMECODE_STRCPY
#define NAMECODE_STRCPY strcpy
#endif
#ifndef NAMECODE_STRCAT
#define NAMECODE_STRCAT strcat
#endif

#endif
