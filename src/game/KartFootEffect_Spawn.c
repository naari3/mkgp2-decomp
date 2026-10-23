extern void KartFootEffect_Tick(void *);
extern unsigned char lbl_80329DB8[];
extern unsigned char *DrawEffect_SpawnDirect(void (*)(void *));
extern void DrawEffect_Free(void *);
extern void Vec3_Copy(void *, const void *);
/* Ghidra exposes this actor as an opaque integer; offsets follow the target. */
void KartFootEffect_Spawn(unsigned char *self) {
    unsigned char *cursor, *row;
    int bank, role, slot;
    unsigned char *child;
    switch (*(int *)(self + 8)) {
    case 2: bank = 0; break;
    case 3: bank = 1; break;
    case 4: bank = 2; break;
    }
    row = lbl_80329DB8 + bank * 9;
    for (role = 0; role < 3; role++, row += 3) {
        cursor = row;
        for (slot = 0; slot < 3; slot++, cursor++) {
            if (*cursor) {
                child = DrawEffect_SpawnDirect(KartFootEffect_Tick);
                if (child) {
                    Vec3_Copy(child + 0x8c, self + 0x8c);
                    child[0x190] = bank;
                    child[0x191] = role;
                    child[0x192] = slot;
                    *(void **)(child + 0x11c) = *(void **)(self + 0x11c);
                }
            }
        }
    }
    DrawEffect_Free(self);
}

