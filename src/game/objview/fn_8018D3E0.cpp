#include "game/ObjViewS22_private.h"
extern "C" {
extern int g_courseVariantIdx, g_longRoundFlag;
extern const float lbl_806D93E0;
extern const char *lbl_80495DF8[5];
void *FUN_8003b120(unsigned long);
}
struct S22List : S22Base {
    clNormal3D **models;
    int count;
    float angle;
    S22List();
    virtual ~S22List();
};
S22List::S22List() {
    int mask=0;
    int i, n;
    models=0;
    count=0;
    angle=lbl_806D93E0;
    switch (g_courseVariantIdx) {
    case 0: if (!g_longRoundFlag) mask=0; else mask=0; break;
    case 1: if (!g_longRoundFlag) mask=5; else mask=8; break;
    case 2: if (!g_longRoundFlag) mask=9; else mask=8; break;
    case 3: if (!g_longRoundFlag) mask=18; else mask=16; break;
    }
    for (i=0;i<5;i++) if (mask & (1<<i)) count++;
    if (count==0) return;
    models=(clNormal3D **)FUN_8003b120(count*4);
    if (!models) { count=0; return; }
    for (i=0;i<count;i++) models[i]=0;
    n=0;
    for (i=0;i<5;i++) {
        if (n>=count) break;
        if (mask & (1<<i)) {
            models[n]=new clNormal3D(lbl_80495DF8[i],0);
            n++;
        }
    }
}
