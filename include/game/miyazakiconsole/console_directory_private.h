#ifndef MIYAZAKI17E_CONSOLE_DIRECTORY_PRIVATE_H
#define MIYAZAKI17E_CONSOLE_DIRECTORY_PRIVATE_H
/* DVD directory ABI mirrors dolphin/dvd.h; its umbrella types header pulls
 * unavailable SDK standard headers in this game compiler configuration. */
struct DVDDir { unsigned long entryNum, location, next; };
struct DVDDirEntry { unsigned long entryNum; int isDir; char *name; };

#endif
