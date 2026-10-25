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
void __construct_array(void*, void (*)(void*), void (*)(void*, short), unsigned long, unsigned long);
}

extern "C" RaceContextSlot* RaceContextArray_Init(RaceContextSlot* self)
{
    __construct_array(self, fn_800A51C4, Unknown_DeleteIfFlag_800a5188, sizeof(RaceContextSlot), 128);
    for (int index = 0; index < 128; index++) {
        self[index].type = -1;
        self[index].id = -1;
        self[index].word08 = 0;
        self[index].word0C = 0;
        self[index].driver = 0;
        self[index].index84 = 0;
        self[index].word88 = 0;
        self[index].word8C = 0;
        self[index].index90 = -1;
        self[index].index94 = -1;
    }
    return self;
}
