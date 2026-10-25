extern void MemoryManager_TimedFree(void *);
extern void dtor_8002CDF4(void *self, short flag);
extern void Sprite_Destroy(void *sprite, int arg);
extern char lbl_8049B5D4[];

void *fn_801D394C(char *self, short flag) {
    if (self != 0) {
        *(char **)self = lbl_8049B5D4;
        Sprite_Destroy(*(void **)(self + 0x10), 1);
        dtor_8002CDF4(self, 0);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
