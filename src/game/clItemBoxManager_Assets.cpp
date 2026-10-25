/*
 * clItemBoxManager channel binding and asset lifetime, 0x8005F194..0x8005F53C.
 */

void *operator new(unsigned long size);

class Normal3D {
public:
    Normal3D(void *desc, int flags);
    unsigned char data[0x5C];
};

class GXChannel {
public:
    GXChannel(void *jobj, void *texObj, int a, int b);
    unsigned char data[0x14];
};

extern "C" {
extern int lbl_806CEEA0;
extern GXChannel *lbl_806D10B0;
extern GXChannel *lbl_806D10B4;
extern GXChannel *lbl_806D10B8;
extern Normal3D *lbl_806D10BC;
extern void *lbl_806D10C0;
extern void *lbl_806D10C4;
extern Normal3D *lbl_806D10C8;
extern void *lbl_806D10CC;
extern char lbl_802EDEF8[];
extern char lbl_802EDF14[];

void DebugPrintf(const char *fmt, ...);
void GXChannel_Bind(GXChannel *channel);
void GXChannel_Unbind(GXChannel *channel);
void dtor_8007D9C4(GXChannel *channel, int flag);
void Object_DtorWithGXSync(void *object, int flag);
void *ResolveJointByName(void *object, const char *name);
void JObj_Hide(void *object, void *jobj, int flags);
void HSD_JObjSetFlags(void *jobj, int flags);
void *HSD_JObjGetDObj(void *jobj);

void clItemBoxManager_UnbindCurrent(void);
void clItemBoxManager_Bind(int index);
void clItemBoxManager_TeardownAssets(void);
void clItemBoxManager_LoadAssets(void);
}

static inline void clItemBoxManager_UnbindInline(void)
{
    switch (lbl_806CEEA0) {
    case 0:
        GXChannel_Unbind(lbl_806D10B4);
        break;
    case 1:
        GXChannel_Unbind(lbl_806D10B0);
        break;
    case 2:
        GXChannel_Unbind(lbl_806D10B8);
        break;
    default:
        DebugPrintf(lbl_802EDF14);
        break;
    }
    lbl_806CEEA0 = -1;
}

void clItemBoxManager_UnbindCurrent(void)
{
    clItemBoxManager_UnbindInline();
}

void clItemBoxManager_Bind(int index)
{
    if (lbl_806CEEA0 != -1) {
        DebugPrintf(lbl_802EDEF8);
        clItemBoxManager_UnbindInline();
    }
    switch (index) {
    case 0:
        GXChannel_Bind(lbl_806D10B4);
        break;
    case 1:
        GXChannel_Bind(lbl_806D10B0);
        break;
    case 2:
        GXChannel_Bind(lbl_806D10B8);
        break;
    default:
        DebugPrintf(lbl_802EDF14);
        break;
    }
    lbl_806CEEA0 = index;
}

void clItemBoxManager_TeardownAssets(void)
{
    dtor_8007D9C4(lbl_806D10B0, 1);
    lbl_806D10B0 = 0;
    dtor_8007D9C4(lbl_806D10B4, 1);
    lbl_806D10B4 = 0;
    dtor_8007D9C4(lbl_806D10B8, 1);
    lbl_806D10B8 = 0;
    Object_DtorWithGXSync(lbl_806D10BC, 1);
    lbl_806D10BC = 0;
    lbl_806D10C0 = 0;
    lbl_806D10C4 = 0;
    Object_DtorWithGXSync(lbl_806D10C8, 1);
    lbl_806D10C8 = 0;
    lbl_806D10CC = 0;
}

void clItemBoxManager_LoadAssets(void)
{
    char *strings = lbl_802EDEF8;

    if (lbl_806D10BC == 0) {
        lbl_806D10BC = new Normal3D(strings + 0x64, 1);
        JObj_Hide(lbl_806D10BC, ResolveJointByName(lbl_806D10BC, strings + 0x74), 0x10);
        lbl_806D10C0 = ResolveJointByName(lbl_806D10BC, strings + 0x90);
        lbl_806D10C4 = ResolveJointByName(lbl_806D10BC, strings + 0xA8);
        HSD_JObjSetFlags(lbl_806D10C4, 0x400);
    }
    if (lbl_806D10C8 == 0) {
        lbl_806D10C8 = new Normal3D(strings + 0x64, 0);
        JObj_Hide(lbl_806D10C8, ResolveJointByName(lbl_806D10C8, strings + 0xC0), 0x10);
        lbl_806D10CC = ResolveJointByName(lbl_806D10C8, strings + 0x74);
    }
    lbl_806D10B0 = new GXChannel(lbl_806D10C0, HSD_JObjGetDObj(lbl_806D10C0), 1, 0);
    lbl_806D10B4 = new GXChannel(lbl_806D10C4, HSD_JObjGetDObj(lbl_806D10C4), 1, 0);
    lbl_806D10B8 = new GXChannel(lbl_806D10CC, HSD_JObjGetDObj(lbl_806D10CC), 1, 0);
}
