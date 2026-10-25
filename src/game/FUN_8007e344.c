typedef struct DVDFileInfo {
    unsigned char cb[0x30];
    unsigned int startAddr;
    unsigned int length;
    void *callback;
} DVDFileInfo;

extern int DVDOpen(const char *path, DVDFileInfo *info);
extern int DVDClose(DVDFileInfo *info);

/* 0x8007E344: length of a disc file, or -1 if it cannot be opened. */
int FUN_8007e344(const char *path)
{
    DVDFileInfo info;
    int length;

    if (DVDOpen(path, &info) == 0) {
        return -1;
    }
    length = info.length;
    DVDClose(&info);
    return length;
}
