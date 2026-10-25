extern int Path_GetCurrentIndex(void *path);

typedef struct PathOwner {
    char pad[0xC];
    void *path;
} PathOwner;

int fn_801DBA34(const PathOwner *self) {
    return Path_GetCurrentIndex(self->path);
}
