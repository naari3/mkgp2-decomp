/* Observed 0xBC-byte slot view; unknown fields remain padding. */
typedef struct RaceContextSlot {
    int type;
    int id;
    unsigned int word08, word0C;
    unsigned char pad10[0x60];
    void* driver;
    unsigned char pad74[0x0C];
    void* position;
    int index84;
    unsigned int word88, word8C;
    int index90, index94;
    unsigned char pad98[4];
    unsigned int word9C;
    unsigned char padA0[4];
    float scale;
    void* item;
    int indexAC;
    int state;
    unsigned int payloadB4;
    unsigned int wordB8;
} RaceContextSlot;

extern "C" {
void Unknown_DeleteIfFlag_800a5188(void*, short);
void fn_800A51C4(void*);
void fn_80270CF4(void*, void (*)(void*, short), unsigned long, unsigned long);
void fn_80270D6C(void*, void (*)(void*), void (*)(void*, short), unsigned long, unsigned long);
void MemoryManager_TimedFree(void*);

RaceContextSlot* RaceContextArray_Dtor(RaceContextSlot* self, short freeFlag)
{
    if (self) {
        fn_80270CF4(self, Unknown_DeleteIfFlag_800a5188, sizeof(RaceContextSlot), 128);
        if (freeFlag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}
}

