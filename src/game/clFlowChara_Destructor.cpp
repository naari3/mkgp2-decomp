/* clFlowChara_Destructor (0x801C4CA4): character select flow teardown. */

struct VObj { virtual ~VObj(); };
typedef struct {
    void *vt;
    char pad04[0x14 - 0x4];
    void *icons[13];
    void *x48[5];
    void *x5C;
    char pad60[0x65 - 0x60];
    unsigned char x65;
    char pad66[0x70 - 0x66];
    VObj *x70;
    void *x74;
    char pad78[0xDC - 0x78];
    void *modelA[13];
    void *modelB[13];
    VObj *holders[13];
    void *x178;
} clFlowChara;

extern "C" {
extern char lbl_8049AC7C[];
extern char *g_pInputState;
extern const float FLOAT_BRIGHTNESS_DARK;
extern void SetScreenBrightness(float b);
extern void fn_80169C44(void);
extern void Sprite_Destroy(void *s, int del);
extern void MemoryManager_TimedFree(void *p);
extern void Object_DtorWithGXSync(void *o, int del);
extern void clRom_PurgeAll(void);
extern void LObjList_Destroy(void *l, int del);
extern void fn_80120A08(int id);
extern void fn_801A1678(void);
extern void dtor_801BA14C(void *self, int del);




}

extern "C" {
#pragma exceptions on
clFlowChara *clFlowChara_Destructor(clFlowChara *self, short del) {
    int i;

    if (self != 0) {
        self->vt = lbl_8049AC7C;
        if ((g_pInputState == 0 ? 0 : g_pInputState) != 0) {
            char *in;
            if ((in = g_pInputState) == 0) {
                in = 0;
            }
            *(unsigned char *)(in + 0x4) = 0;
            *(int *)(in + 0x18) = 0;
            *(int *)(in + 0x1C) = 0;
        }
        SetScreenBrightness(FLOAT_BRIGHTNESS_DARK);
        fn_80169C44();
        Sprite_Destroy(self->x48[0], 1);
        Sprite_Destroy(self->x48[1], 1);
        Sprite_Destroy(self->x48[2], 1);
        Sprite_Destroy(self->x48[3], 1);
        Sprite_Destroy(self->x48[4], 1);
        if (self->x178 != 0) {
            MemoryManager_TimedFree(self->x178);
        }
        for (i = 0; i < 13; i++) {
            Object_DtorWithGXSync(self->modelA[i], 1);
            Object_DtorWithGXSync(self->modelB[i], 1);
            delete self->holders[i];
        }
        clRom_PurgeAll();
        delete self->x70;
        LObjList_Destroy(self->x74, 1);
        self->x70 = 0;
        self->x74 = 0;
        self->x65 = 0;
        fn_80120A08(0x167F);
        fn_80120A08(0x169B);
        fn_80120A08(0x16AC);
        fn_80120A08(0x16AE);
        fn_80120A08(0x16AD);
        fn_80120A08(0x16AF);
        fn_80120A08(0x16A8);
        for (i = 0; i < 13; i++) {
            Sprite_Destroy(self->icons[i], 1);
        }
        Sprite_Destroy(self->x5C, 1);
        fn_801A1678();
        dtor_801BA14C(self, 0);
        if (del > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#pragma exceptions reset
}
