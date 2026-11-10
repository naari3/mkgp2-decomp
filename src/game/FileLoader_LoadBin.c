#include "game/types/FileLoader.h"

extern int g_romActiveCount;
extern int g_romActiveCountPeak;
extern FileLoader *g_romListHead;
extern FileLoader *g_romListTail;
extern char lbl_802E9800[];
extern void *DVDLoad_OpenAllocReadRelocSync(char *path);
extern void DebugPrintf(const char *, ...);

FileLoader *FileLoader_LoadBin(FileLoader *loader, char *path) {
    int attempt;

    g_romActiveCount++;
    if (g_romActiveCountPeak < g_romActiveCount) {
        g_romActiveCountPeak = g_romActiveCount;
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
    if (g_romListHead == 0) {
        g_romListHead = loader;
        g_romListTail = loader;
    } else {
        loader->prev = g_romListTail;
        g_romListTail->next = loader;
        g_romListTail = loader;
    }
    return loader;
}
