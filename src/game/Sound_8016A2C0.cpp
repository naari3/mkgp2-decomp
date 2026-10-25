/*
 * 0x8016A2C0..0x8016A3D4: looping sound emitter tick and its deleting
 * destructor (vtable lbl_8049102C, base vtable lbl_80490FE0).
 */

struct LoopSE {
    void *vtable;
    void *pos;
    int volume;
    unsigned char playing;
};

extern "C" {
extern char lbl_8049102C[];
extern char lbl_80490FE0[];
extern char lbl_8036C9B4[];
extern unsigned char SoundMgr_PlaySE(int);
extern void fn_8016C240(int, void *, int);
extern void fn_8016C394(int);
extern void MemoryManager_Free(void *);
extern void MemoryManager_TimedFree(void *);
extern void DebugPrintf(const char *, ...);

#pragma exceptions on

void fn_8016A2C0(LoopSE *self) {
    if (self->volume == 0 || self->pos == 0) {
        return;
    }
    if (!self->playing) {
        self->playing = SoundMgr_PlaySE(0x2A);
    }
    fn_8016C240(0x2A, self->pos, self->volume);
}

LoopSE *fn_8016A32C(LoopSE *self, short flag) {
    if (self) {
        self->vtable = lbl_8049102C;
        if (self->pos) {
            MemoryManager_Free(self->pos);
        }
        if (self->playing) {
            fn_8016C394(0x2A);
            self->playing = 0;
        }
        DebugPrintf(lbl_8036C9B4);
        if (self) {
            self->vtable = lbl_80490FE0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

#pragma exceptions reset
}
