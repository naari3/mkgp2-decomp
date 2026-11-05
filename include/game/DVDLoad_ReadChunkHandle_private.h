#ifndef DVDLOAD_READCHUNKHANDLE_PRIVATE_H
#define DVDLOAD_READCHUNKHANDLE_PRIVATE_H
typedef struct DVDLoadFile {
    unsigned char commandBlock[0x30];
    unsigned long startAddr;
    unsigned long length;
} DVDLoadFile;
#endif
