typedef struct FileLoader {
    int state;
    char *path;
    struct FileLoader *prev;
    struct FileLoader *next;
    void *data;
    unsigned char done;
} FileLoader;

extern int lbl_806D0FE8;
extern int lbl_806D0FEC;
extern FileLoader *lbl_806D0FE0;
extern FileLoader *lbl_806D0FE4;
extern char lbl_802E9800[];
extern void *DVDLoad_OpenAllocReadRelocSync(char *path);
extern void DebugPrintf(const char *, ...);

FileLoader *FileLoader_LoadBin(FileLoader *loader, char *path) {
    int attempt;

    lbl_806D0FE8++;
    if (lbl_806D0FEC < lbl_806D0FE8) {
        lbl_806D0FEC = lbl_806D0FE8;
    }
    loader->done = 0;
    loader->state = 1;
    loader->path = path;
    loader->prev = 0;
    loader->next = 0;
    loader->data = 0;
    attempt = 1;
    while ((loader->data = DVDLoad_OpenAllocReadRelocSync(path)) == 0) {
        attempt++;
        DebugPrintf(lbl_802E9800, attempt);
    }
    if (lbl_806D0FE0 == 0) {
        lbl_806D0FE0 = loader;
        lbl_806D0FE4 = loader;
    } else {
        loader->prev = lbl_806D0FE4;
        lbl_806D0FE4->next = loader;
        lbl_806D0FE4 = loader;
    }
    return loader;
}
