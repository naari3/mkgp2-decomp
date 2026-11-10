#ifndef GAME_MAP_SWITCH_BOUNDS_PRIVATE_H
#define GAME_MAP_SWITCH_BOUNDS_PRIVATE_H
#include "game/types/size_t.h"
#include "sysdolphin/baselib/jobj.h"
struct SwitchVec { float x,y,z; };
extern "C" {
extern const float lbl_806D8E98, lbl_806D8E9C, lbl_806D8EA0;
extern int g_cupId, g_longRoundFlag;
HSD_JObj *ResolveJointByName(void *, const char *);
void HSD_JObjClearFlags(HSD_JObj *, unsigned int);
void HSD_JObjSetFlags(HSD_JObj *, unsigned int);
unsigned char fn_801847DC(HSD_JObj *, SwitchVec *, SwitchVec *);
float Vec3_Magnitude(SwitchVec *);
}
void *operator new(size_t);
void operator delete(void *);
struct SwitchNode {
    SwitchNode *next;
    HSD_JObj *shown,*hidden;
    SwitchVec center;
    float radius, value;
    SwitchNode(HSD_JObj *a,HSD_JObj *b) {
        next=0;shown=0;hidden=0;
        center.x=lbl_806D8E98;center.y=lbl_806D8E98;center.z=lbl_806D8E98;radius=lbl_806D8E98;value=lbl_806D8E98;
        if (!a || !b) return;
        shown=a;hidden=b;
        SwitchVec lo={0.0f,0.0f,0.0f};
        SwitchVec hi={0.0f,0.0f,0.0f};
        HSD_JObjClearFlags(shown,0x10);
        HSD_JObjClearFlags(hidden,0x10);
        if (!fn_801847DC(b,&lo,&hi)) return;
        center.x=lbl_806D8E9C*(hi.x+lo.x);
        center.y=lbl_806D8E9C*(hi.y+lo.y);
        center.z=lbl_806D8E9C*(hi.z+lo.z);
        hi.x-=center.x;
        hi.y-=center.y;
        hi.z-=center.z;
        radius=Vec3_Magnitude(&hi);
        value=lbl_806D8EA0;
    }
};
struct SwitchList {
    SwitchNode *head;
    void Append(SwitchNode *n) {
        if (!n) return;
        if (!head) head=n;
        else {
            SwitchNode *p=head;
            while (p->next) p=p->next;
            p->next=n;
        }
        n->next=0;
    }
    SwitchList(void *root);
};

#endif
