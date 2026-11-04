#include "../src/game/mapeffect/mapfx16a_private.h"
struct KiriJoint16A {
    char pad[8];
    KiriJoint16A *next;
    KiriJoint16A *parent;
    KiriJoint16A *child;
    unsigned int flags;
    char pad18[0x2c];
    float mtx[3][4];
};
struct Kiri16A : MapPart16A {
    Vec3f *positions;
    int count;
    unsigned char playing;
    Kiri16A(KiriJoint16A *);
    virtual ~Kiri16A();
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
Kiri16A::Kiri16A(KiriJoint16A *root) {
    DebugPrintf(lbl_8036C9D8);
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
