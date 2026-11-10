struct HSD_JObj;
struct Pair { const char *a,*b; };
extern "C" {
extern int g_cupId,g_courseVariantIdx;
extern const char *lbl_806CFC58,*lbl_806CFC5C,*lbl_806CFC60;
extern const float lbl_806D94B8;
void DebugPrintf(const char *,...);
void fn_801825FC();
void fn_801825C8();
void fn_8018F7D4(void *,void *);
}
// Ripple resource names and paired joints share one compiler constant pool.
static const char lbl_80378210[11] = "ripple.dat";
static const char lbl_8037821C[29] = "ef_MR_ripple_ripple_a1_joint";
static const char lbl_8037823C[29] = "ef_MR_ripple_ripple_a2_joint";
static const char lbl_8037825C[29] = "ef_MR_ripple_ripple_b1_joint";
static const char lbl_8037827C[29] = "ef_MR_ripple_ripple_b2_joint";
static const char lbl_8037829C[29] = "ef_MR_ripple_ripple_c1_joint";
static const char lbl_803782BC[29] = "ef_MR_ripple_ripple_c2_joint";
static const Pair lbl_803782DC[3] = { {lbl_8037821C, lbl_8037823C}, {lbl_8037825C, lbl_8037827C}, {lbl_8037829C, lbl_803782BC} };
static const char lbl_803782F4[14] = "ripple_tw.dat";
static const char lbl_80378304[32] = "ef_MR_ripple_tw_ripple_a1_joint";
static const char lbl_80378324[32] = "ef_MR_ripple_tw_ripple_a2_joint";
static const char lbl_80378344[32] = "ef_MR_ripple_tw_ripple_b1_joint";
static const char lbl_80378364[32] = "ef_MR_ripple_tw_ripple_b2_joint";
static const char lbl_80378384[32] = "ef_MR_ripple_tw_ripple_c1_joint";
static const char lbl_803783A4[32] = "ef_MR_ripple_tw_ripple_c2_joint";
static const Pair lbl_803783C4[3] = { {lbl_80378304, lbl_80378324}, {lbl_80378344, lbl_80378364}, {lbl_80378384, lbl_803783A4} };
static const char lbl_803783DC[14] = "ripple_ni.dat";
static const char lbl_803783EC[32] = "ef_MR_ripple_ni_ripple_a1_joint";
static const char lbl_8037840C[32] = "ef_MR_ripple_ni_ripple_a2_joint";
static const char lbl_8037842C[32] = "ef_MR_ripple_ni_ripple_b1_joint";
static const char lbl_8037844C[32] = "ef_MR_ripple_ni_ripple_b2_joint";
static const char lbl_8037846C[32] = "ef_MR_ripple_ni_ripple_c1_joint";
static const char lbl_8037848C[32] = "ef_MR_ripple_ni_ripple_c2_joint";
static const Pair lbl_803784AC[3] = { {lbl_803783EC, lbl_8037840C}, {lbl_8037842C, lbl_8037844C}, {lbl_8037846C, lbl_8037848C} };
static const char lbl_803784C4[9] = "clRipple";
static const char lbl_803784D0[17] = "clMapEffectParts";
static const char lbl_803784E4[29] = " DeleteMapEffect : clRipple\n";
static const char lbl_80378504[29] = " CreateMapEffect : clRipple\n";

#include "game/types/clNormal3D.h"
extern "C" HSD_JObj *ResolveJointByName(clNormal3D *,const char *);
struct MorphNode { char data[0x38]; MorphNode(HSD_JObj *,HSD_JObj *); };
struct MorphBase { MorphBase() {} virtual ~MorphBase(); };
struct MorphView : MorphBase {
    clNormal3D *model;
    float phase;
    MorphNode *head;
    MorphView();
    virtual ~MorphView();
};
MorphView::MorphView() {
    const char *cursor;
    HSD_JObj *b;
    HSD_JObj *a;
    const Pair *pairs;
    const char *name;
    int count;
    DebugPrintf(lbl_80378504);
    model=0; head=0; phase=lbl_806D94B8;
    name=0; pairs=0; count=0;
    switch (g_cupId) {
    case 1:
        switch (g_courseVariantIdx) {
        case 0: name=lbl_806CFC58; pairs=lbl_803782DC; count=3; break;
        case 1: name=lbl_806CFC5C; pairs=lbl_803783C4; count=3; break;
        case 2: name=lbl_806CFC60; pairs=lbl_803784AC; count=3; break;
        }
        break;
    case 9: name=lbl_806CFC58; pairs=lbl_803782DC; count=3; break;
    }
    if (!name || !pairs) return;
    fn_801825FC();
    model=new clNormal3D(name,0);
    fn_801825C8();
    cursor=(const char *)pairs;
    for (int i=0;i<count;cursor+=8,i++) {
        a=ResolveJointByName(model,((const Pair *)cursor)->a);
        b=ResolveJointByName(model,((const Pair *)cursor)->b);
        if (a && b) {
            MorphNode *n=new MorphNode(a,b);
            if (head) fn_8018F7D4(head,n);
            else head=n;
        }
    }
}
