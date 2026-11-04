#include "game/mapobject/mapobject.h"
struct CourseRodata { char pad0[0x55C]; const void *normal[13]; char pad590[0x104]; const void *other[13]; char pad6c8[0x14]; char log[0x2C]; char extra[0x10]; char joint[0x1C]; char ready[4]; };
extern "C" const CourseRodata lbl_803BF440;
struct ModelPair {
    int id;
    clNormal3D *obj[2];
    ModelPair(int n) : id(n) {
        obj[0] = 0;
        obj[1] = 0;
        for (int i = 0; i < 2; i++) {
            const void *desc = 0;
            int index = id;
            if (!obj[i]) {
                switch (i) {
                case 0:
                    if (!(index > -1 && index < 13)) index = 0;
                    desc = lbl_803BF440.normal[index];
                    break;
                case 1:
                    if (!(index > -1 && index < 13)) index = 0;
                    desc = lbl_803BF440.other[index];
                    break;
                }
                if (desc) obj[i] = new clNormal3D(desc, 0);
            }
        }
    }
};
struct ModelBank {
    ModelPair *pairs[13];
    ModelBank() {
        DebugPrintf(lbl_803BF440.log);
        for (int i = 0; i < 13; i++) pairs[i] = new ModelPair(i);
    }
};
extern "C" ModelBank *lbl_806D19B4;
extern "C" ModelBank *fn_801F9B64() {
    if (!lbl_806D19B4) lbl_806D19B4 = new ModelBank;
    return lbl_806D19B4;
}
