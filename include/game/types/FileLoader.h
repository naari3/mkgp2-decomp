#ifndef GAME_TYPES_FILELOADER_H
#define GAME_TYPES_FILELOADER_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct FileLoader FileLoader;
struct FileLoader {
    /* 0x000 */ int state;
    /* 0x004 */ char *path;
    /* 0x008 */ struct FileLoader *prev;
    /* 0x00C */ struct FileLoader *next;
    /* 0x010 */ void *data;
    /* 0x014 */ unsigned char done;
    /* 0x015 */ unsigned char pad_015[0x3];
};

#endif /* GAME_TYPES_FILELOADER_H */
