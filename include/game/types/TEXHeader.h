#ifndef GAME_TYPES_TEXHEADER_H
#define GAME_TYPES_TEXHEADER_H

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct TEXHeader TEXHeader;
struct TEXHeader {
    /* 0x000 */ unsigned short height;
    /* 0x002 */ unsigned short width;
    /* 0x004 */ unsigned int format;
    /* 0x008 */ void *data;
    /* 0x00C */ unsigned int wrapS;
    /* 0x010 */ unsigned int wrapT;
    /* 0x014 */ unsigned int minFilter;
    /* 0x018 */ unsigned int magFilter;
    /* 0x01C */ float lodBias;
    /* 0x020 */ unsigned char edgeLODEnable;
    /* 0x021 */ unsigned char minLOD;
    /* 0x022 */ unsigned char maxLOD;
    /* 0x023 */ unsigned char pad_023[0x1];
};

#endif /* GAME_TYPES_TEXHEADER_H */
