extern int FUN_8007e344(char *path);
extern void *FUN_8003b120(int size);
extern void FUN_8007dfe4(char *path, void *buf, int size, int offset, int flags);

void *DVDFile_LoadSync(char *path) {
    int size = (FUN_8007e344(path) + 0x1F) & ~0x1F;
    void *buf = FUN_8003b120(size);

    FUN_8007dfe4(path, buf, size, 0, 0);
    return buf;
}
