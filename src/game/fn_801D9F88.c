extern void MemoryManager_TimedFree(void *);
extern void Sprite_Destroy(void *sprite, int arg);

static inline void FreeBuffer(void *p) {
    if (p != 0) {
        MemoryManager_TimedFree(p);
    }
}

typedef struct Obj801D9F88 {
    char pad0[0x48];
    void *sprite48;
    void *sprite4C;
    void *bufA[3];
    void *bufB[3];
} Obj801D9F88;

void *fn_801D9F88(Obj801D9F88 *self, short flag) {
    int i;

    if (self != 0) {
        if (self->sprite48 != 0) {
            Sprite_Destroy(self->sprite48, 1);
            self->sprite48 = 0;
        }
        if (self->sprite4C != 0) {
            Sprite_Destroy(self->sprite4C, 1);
            self->sprite4C = 0;
        }
        for (i = 0; i < 3; i++) {
            if (self->bufA[i] != 0) {
                FreeBuffer(self->bufA[i]);
                self->bufA[i] = 0;
            }
        }
        for (i = 0; i < 3; i++) {
            if (self->bufB[i] != 0) {
                FreeBuffer(self->bufB[i]);
                self->bufB[i] = 0;
            }
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
