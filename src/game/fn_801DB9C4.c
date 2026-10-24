extern int Path_GetTotalCount(void *path);
extern void *Path_GetWaypointPtr(void *path, int idx);

void *fn_801DB9C4(char *self, int offset) {
    void *path = *(void **)(self + 0xC);
    int total = Path_GetTotalCount(path);
    return Path_GetWaypointPtr(path, (offset + Path_GetTotalCount(path)) % total);
}
