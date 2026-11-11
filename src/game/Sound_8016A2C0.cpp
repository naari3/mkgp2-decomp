/* clDKFallSound: waterfall sound positions collected from child joints. */
#include "game/mapobject/mapobject.h"
#include "game/types/clMapEffectParts.h"

void operator delete(void *) throw();
struct KiriJoint16A;
struct clDKFallSound : clMapEffectParts {
    Vec3f *positions;
    int count;
    unsigned char playing;
    virtual ~clDKFallSound();
    virtual void Update();
    clDKFallSound(KiriJoint16A *);
};
extern "C" {
unsigned char SoundMgr_PlaySE(int);
void fn_8016C240(int, void *, int);
void fn_8016C394(int);
void MemoryManager_Free(void *);
void DebugPrintf(const char *, ...);
void *FUN_8003b120(unsigned long);
}

struct KiriJoint16A {
    char pad[8];
    KiriJoint16A *next;
    KiriJoint16A *parent;
    KiriJoint16A *child;
    unsigned int flags;
    char pad18[0x2c];
    float mtx[3][4];
};
extern "C" {
extern char lbl_806D8A30[7], lbl_806D8A38[5];
extern const char lbl_8036C9D8[];
void HSD_JObjSetupMatrixSub(HSD_JObj *);
}
static inline unsigned char Dirty(KiriJoint16A *j) {
    if (!j) __assert(lbl_806D8A30, 0x25d, lbl_806D8A38);
    unsigned char ret=0;
    if (!(j->flags & 0x800000) && (j->flags & 0x40)) ret=1;
    return ret;
}
static inline float (*Matrix(KiriJoint16A *j))[4] {
    if (!j) __assert(lbl_806D8A30, 0x47c, lbl_806D8A38);
    if (j && Dirty(j)) HSD_JObjSetupMatrixSub((HSD_JObj *)j);
    return j->mtx;
}
clDKFallSound::clDKFallSound(KiriJoint16A *root) {
    DebugPrintf(" CreateMapEffect : clDKFallSound\n");
    positions = 0;
    count = 0;
    playing = 0;
    if (!root) return;
    KiriJoint16A *j;
    for (j=(root == 0 ? 0 : root->child); j; j=(j == 0 ? 0 : j->next)) count++;
    if (count) {
        positions=(Vec3f *)FUN_8003b120(count * sizeof(Vec3f));
        int i=0;
        for (j=(root == 0 ? 0 : root->child); j; j=(j == 0 ? 0 : j->next)) {
            if (i >= count) break;
            positions[i].x=Matrix(j)[0][3];
            positions[i].y=Matrix(j)[1][3];
            positions[i].z=Matrix(j)[2][3];
            ++i;
        }
    }
}

clDKFallSound::~clDKFallSound() {
    if (positions) {
        MemoryManager_Free(positions);
    }
    if (playing) {
        fn_8016C394(0x2A);
        playing = 0;
    }
    DebugPrintf(" DeleteMapEffect : clDKFallSound\n");
}

void clDKFallSound::Update() {
    if (count == 0 || positions == 0) {
        return;
    }
    if (!playing) {
        playing = SoundMgr_PlaySE(0x2A);
    }
    fn_8016C240(0x2A, positions, count);
}
