/*
 * 0x8014CE74..0x8014D540: small helpers of the result-screen 3D parts:
 * a factory, two- and three-model holders (update, colour and release) and
 * two thin virtual forwarders. The holder ctors index this area's pooled
 * .rodata; the two-model one (fn_8014D038) is still asm.
 */
#pragma cplusplus on

void *operator new(unsigned long);
void operator delete(void *);

struct VObj {
    virtual ~VObj();
};

struct Part3D;

extern "C" {
extern void fn_8013D4B0(Part3D *p, float t);
extern void fn_8013DAC8(Part3D *p, int a);
extern void fn_8013D50C(Part3D *p, float r, float g, float b, float a);
extern void HSD_StateInvalidate(int n);
extern void Frame_PostDrawOverlay(void);
extern void Frame_UpdatePerFrameState(void);
}

struct Scene3DObj {
    char pad[0x74];
    Scene3DObj();
};

struct PairHolder {
    int arg;
    Part3D *parts[2];
    ~PairHolder();
};

struct TripleHolder {
    int arg;
    Part3D *parts[3];
    ~TripleHolder();
};

struct Runner {
    virtual void m08();
    virtual void m0C();
    virtual void m10();
    virtual void m14();
    virtual void m18();
};

struct RunnerOwner {
    int m0;
    int m4;
    Runner *runner;
};

struct ResultScene {
    char pad[0x50];
    ResultScene();
};

extern "C" {
extern void Alloc();
extern void fn_8013D59C(Part3D *p, float x, float y, float z);
extern void fn_8013D608(Part3D *p, float x, float y, float z);
extern void fn_8013D634(Part3D *p, float x, float y, float z);
extern void fn_8013D660(Part3D *p, float x, float y);
extern void fn_8013D738(Part3D *p, float sx, float sy);
extern void *ItemRes_LookupByKey_Thunk(int key);
extern void fn_8013D800();
extern const float lbl_806D7E2C;
extern const float lbl_806D7E30;
extern const float lbl_806D7EF4;
extern unsigned int CSSceneGetTitle_8014ADB4_rodata_80362D90[];
extern void MemoryManager_TimedFree();
extern float lbl_806D7EE4;
PairHolder *fn_8014D038(PairHolder *h, int arg, float x, float y, float s);
TripleHolder *fn_8014D344(TripleHolder *h, int arg, float x, float y, float s);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; void *f7; unsigned int f8; void *f9; } extab_fn_8014D038 = { 0x21CA0000, 0x0000008C, 0x00000018, 0x000000AC, 0x00000020, 0x00000000, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree };


#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014D038 = {
    (void *)&fn_8014D038, 0x000001A8, (void *)&extab_fn_8014D038
};


}


extern "C" void fn_8014CE74(VObj *p) {
    delete p;
}

extern "C" Scene3DObj *fn_8014CEAC(void) {
    return new Scene3DObj();
}

extern "C" void fn_8014CEE8(PairHolder *h, float t) {
    int i;

    for (i = 0; i < 2; i++) {
        fn_8013D4B0(h->parts[i], t);
    }
}

extern "C" void fn_8014CF44(PairHolder *h) {
    int i;

    for (i = 0; i < 2; i++) {
        fn_8013DAC8(h->parts[i], h->arg);
    }
}

extern "C" void fn_8014CFA0(void) {
}

PairHolder::~PairHolder() {
    int i;

    for (i = 0; i < 2; i++) {
        delete (VObj *)parts[i];
    }
}

struct PreviewPart {
    char pad[0x20];
    PreviewPart(void *resource, unsigned char flag);
};
struct PartVec { float x, y, z; };
extern "C" PairHolder *fn_8014D038(PairHolder *h, int arg, float x, float y, float s) {
    PartVec *pos = (PartVec *)CSSceneGetTitle_8014ADB4_rodata_80362D90;
    PartVec *rot;
    float k, rx, ry, rz;
    int i;

    h->arg = arg;
    h->parts[0] = (Part3D *)new PreviewPart((char *)pos + 0xF74, 1);
    h->parts[1] = (Part3D *)new PreviewPart((char *)pos + 0xF88, 1);
    rot = (PartVec *)((char *)pos + 0xEF4);
    k = lbl_806D7EF4;
    rx = rot->x;
    pos = (PartVec *)((char *)pos + 0xED0);
    ry = rot->y;
    rz = rot->z;
    for (i = 0; i < 2; i++) {
        fn_8013D738(h->parts[i], lbl_806D7E30, lbl_806D7E2C);
        fn_8013D660(h->parts[i], x, y);
        fn_8013D634(h->parts[i], pos->x * s, pos->y * s, pos->z * s);
        fn_8013D608(h->parts[i], s, s, s);
        fn_8013D59C(h->parts[i], k * rx, k * ry, k * rz);
        pos++;
    }
    return h;
}

extern "C" void fn_8014D1E0(TripleHolder *h, float a) {
    int i;

    for (i = 0; i < 3; i++) {
        fn_8013D50C(h->parts[i], 2.0f, 2.0f, 2.0f, a);
    }
}

extern "C" void fn_8014D250(TripleHolder *h) {
    int i;

    for (i = 0; i < 3; i++) {
        fn_8013DAC8(h->parts[i], h->arg);
    }
}

extern "C" void fn_8014D2AC(void) {
}

TripleHolder::~TripleHolder() {
    int i;

    for (i = 0; i < 3; i++) {
        delete (VObj *)parts[i];
    }
}


/* Three-model holder ctor body: one preview model per slot, placed from
 * this area's pooled layout tables (positions, rotations in degrees, scales).
 * fakematch (permuter): the slot cursor `c` walks the holder 4 bytes at a
 * time so that the parts pointer gets the target's register; the natural code
 * is `h->parts[i]` with i as the loop index. */
extern "C" TripleHolder *fn_8014D344(TripleHolder *h, int arg, float x, float y, float s) {
    float *scale = (float *)((char *)CSSceneGetTitle_8014ADB4_rodata_80362D90 + 0xEB8);
    PartVec *pos = (PartVec *)((char *)CSSceneGetTitle_8014ADB4_rodata_80362D90 + 0xE70);
    PartVec *rot = (PartVec *)((char *)CSSceneGetTitle_8014ADB4_rodata_80362D90 + 0xE94);
    TripleHolder *c = h;
    float k;
    int i;

    h->arg = arg;
    k = lbl_806D7EF4;
    for (i = 0; i < 3; i++) {
        c->parts[0] = (Part3D *)new PreviewPart(ItemRes_LookupByKey_Thunk(0x32), 1);
        fn_8013D738(c->parts[0], lbl_806D7E30, lbl_806D7E2C);
        fn_8013D660(c->parts[0], x, y);
        fn_8013D634(c->parts[0], pos->x * s, pos->y * s, pos->z * s);
        fn_8013D608(c->parts[0], *scale * s, *scale * s, *scale * s);
        fn_8013D59C(c->parts[0], k * rot->x, k * rot->y, k * rot->z);
        fn_8013D50C(c->parts[0], lbl_806D7EE4, lbl_806D7EE4, lbl_806D7EE4, lbl_806D7E30);
        scale++;
        pos++;
        rot++;
        c = (TripleHolder *)&c->parts[0];
    }
    return h;
}

extern "C" void fn_8014D4B8(RunnerOwner *o) {
    o->runner->m14();
    HSD_StateInvalidate(-1);
}

extern "C" void fn_8014D4F0(RunnerOwner *o) {
    o->runner->m10();
    o->runner->m18();
}
