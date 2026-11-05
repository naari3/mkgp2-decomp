#ifndef GAME_COLLISION_FILE_LOAD_PRIVATE_H
#define GAME_COLLISION_FILE_LOAD_PRIVATE_H
typedef unsigned long u32;
/* DVDFileInfo ABI from dolphin/dvd.h; its umbrella headers require a
 * different C library include profile from the game translation units. */
typedef struct CollisionDVDFileInfo {
    unsigned char commandBlock[0x30];
    u32 startAddr;
    u32 length;
    void *callback;
} CollisionDVDFileInfo;
extern int DVDOpen(const char *, CollisionDVDFileInfo *);
extern int DVDReadPrio(CollisionDVDFileInfo *, void *, int, int, int);
extern int DVDClose(CollisionDVDFileInfo *);
#endif

