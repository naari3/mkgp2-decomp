#include "game/mapobject/mapobject.h"
/* Shared animation and model resource pool. */
static const float animationScale[3] = {1.0f, 0.7f, 0.9f};
struct AnimationKey { float frame, value; };
static const AnimationKey animationKeys[18][7] = {
    { {0.0f, 0.0f}, {500.0f, 66.66667f}, {1000.0f, 66.66667f}, {2000.0f, 66.66667f}, {3000.0f, 66.66667f}, {4000.0f, 66.66667f}, {5000.0f, 66.66667f} },
    { {0.0f, 0.0f}, {500.0f, 66.66667f}, {1000.0f, 66.66667f}, {2000.0f, 66.66667f}, {3000.0f, 66.66667f}, {4000.0f, 66.66667f}, {5000.0f, 66.66667f} },
    { {0.0f, 0.0f}, {500.0f, 66.66667f}, {1000.0f, 66.66667f}, {2000.0f, 66.66667f}, {3000.0f, 66.66667f}, {4000.0f, 66.66667f}, {5000.0f, 66.66667f} },
    { {0.0f, 0.0f}, {500.0f, 66.66667f}, {1000.0f, 66.66667f}, {2000.0f, 66.66667f}, {3000.0f, 66.66667f}, {4000.0f, 66.66667f}, {5000.0f, 66.66667f} },
    { {0.0f, 0.0f}, {500.0f, 66.66667f}, {1000.0f, 66.66667f}, {2000.0f, 66.66667f}, {3000.0f, 66.66667f}, {4000.0f, 66.66667f}, {5000.0f, 66.66667f} },
    { {0.0f, 0.0f}, {500.0f, 66.66667f}, {1000.0f, 66.66667f}, {2000.0f, 66.66667f}, {3000.0f, 66.66667f}, {4000.0f, 66.66667f}, {5000.0f, 66.66667f} },
    { {0.0f, 0.0f}, {500.0f, 66.66667f}, {1000.0f, 66.66667f}, {2000.0f, 66.66667f}, {3000.0f, 66.66667f}, {4000.0f, 66.66667f}, {5000.0f, 66.66667f} },
    { {0.0f, 0.0f}, {500.0f, 66.66667f}, {1000.0f, 66.66667f}, {2000.0f, 66.66667f}, {3000.0f, 66.66667f}, {4000.0f, 66.66667f}, {5000.0f, 66.66667f} },
    { {0.0f, 0.0f}, {500.0f, 66.66667f}, {1000.0f, 66.66667f}, {2000.0f, 66.66667f}, {3000.0f, 66.66667f}, {4000.0f, 66.66667f}, {5000.0f, 66.66667f} },
    { {0.0f, 0.0f}, {500.0f, 66.66667f}, {1000.0f, 66.66667f}, {2000.0f, 66.66667f}, {3000.0f, 66.66667f}, {4000.0f, 66.66667f}, {5000.0f, 66.66667f} },
    { {0.0f, 0.0f}, {500.0f, 66.66667f}, {1000.0f, 66.66667f}, {2000.0f, 66.66667f}, {3000.0f, 66.66667f}, {4000.0f, 66.66667f}, {5000.0f, 66.66667f} },
    { {0.0f, 0.0f}, {500.0f, 66.66667f}, {1000.0f, 66.66667f}, {2000.0f, 66.66667f}, {3000.0f, 66.66667f}, {4000.0f, 66.66667f}, {5000.0f, 66.66667f} },
    { {0.0f, 0.0f}, {500.0f, 83.333336f}, {1000.0f, 83.333336f}, {2000.0f, 83.333336f}, {3000.0f, 83.333336f}, {4000.0f, 83.333336f}, {5000.0f, 83.333336f} },
    { {0.0f, 0.0f}, {500.0f, 83.333336f}, {1000.0f, 83.333336f}, {2000.0f, 83.333336f}, {3000.0f, 83.333336f}, {4000.0f, 83.333336f}, {5000.0f, 83.333336f} },
    { {0.0f, 0.0f}, {500.0f, 83.333336f}, {1000.0f, 83.333336f}, {2000.0f, 83.333336f}, {3000.0f, 83.333336f}, {4000.0f, 83.333336f}, {5000.0f, 83.333336f} },
    { {0.0f, 0.0f}, {500.0f, 83.333336f}, {1000.0f, 83.333336f}, {2000.0f, 83.333336f}, {3000.0f, 83.333336f}, {4000.0f, 83.333336f}, {5000.0f, 83.333336f} },
    { {0.0f, 0.0f}, {500.0f, 83.333336f}, {1000.0f, 83.333336f}, {2000.0f, 83.333336f}, {3000.0f, 83.333336f}, {4000.0f, 83.333336f}, {5000.0f, 83.333336f} },
    { {0.0f, 0.0f}, {500.0f, 83.333336f}, {1000.0f, 83.333336f}, {2000.0f, 83.333336f}, {3000.0f, 83.333336f}, {4000.0f, 83.333336f}, {5000.0f, 83.333336f} },
};
extern "C" {
extern const char lbl_806DA778[];
extern const char lbl_806DA780[];
extern const char lbl_806DA788[];
extern const char lbl_806DA790[];
extern const char lbl_806DA798[];
extern const char lbl_806DA7A0[];
extern const char lbl_806DA7A8[];
extern const char lbl_806DA7B0[];
extern const char lbl_806DA7B8[];
extern const char lbl_806DA7C0[];
extern const char lbl_806DA7C8[];
extern const char lbl_806DA7D0[];
}
static const char msPacman[] = "MSPACMAN";
static const char *const characterNames[13] = {lbl_806DA778,lbl_806DA780,lbl_806DA788,lbl_806DA790,lbl_806DA798,lbl_806DA7A0,lbl_806DA7A8,lbl_806DA7B0,lbl_806DA7B8,msPacman,lbl_806DA7C0,lbl_806DA7C8,lbl_806DA7D0};
static const char demo_803BF87C[] = "kart_demo_mario.dat";
static const char demo_803BF890[] = "kart_demo_luigi.dat";
static const char demo_803BF8A4[] = "kart_demo_wario.dat";
static const char demo_803BF8B8[] = "kart_demo_peach.dat";
static const char demo_803BF8CC[] = "kart_demo_koopa.dat";
static const char demo_803BF8E0[] = "kart_demo_kinopio.dat";
static const char demo_803BF8F8[] = "kart_demo_donkey.dat";
static const char demo_803BF910[] = "kart_demo_yoshi.dat";
static const char demo_803BF924[] = "kart_demo_pacman.dat";
static const char demo_803BF93C[] = "kart_demo_mspacman.dat";
static const char demo_803BF954[] = "kart_demo_monster.dat";
static const char demo_803BF96C[] = "kart_demo_waluigi.dat";
static const char demo_mametch[] = "kart_demo_mametch.dat";
static const void *const demoModels[13] = {demo_803BF87C, demo_803BF890, demo_803BF8A4, demo_803BF8B8, demo_803BF8CC, demo_803BF8E0, demo_803BF8F8, demo_803BF910, demo_803BF924, demo_803BF93C, demo_803BF954, demo_803BF96C, demo_mametch};
static const char select_803BF9D0[] = "select_mario.dat";
static const char select_803BF9E4[] = "select_luigi.dat";
static const char select_803BF9F8[] = "select_wario.dat";
static const char select_803BFA0C[] = "select_peach.dat";
static const char select_803BFA20[] = "select_koopa.dat";
static const char select_803BFA34[] = "select_kinopio.dat";
static const char select_803BFA48[] = "select_donkey.dat";
static const char select_803BFA5C[] = "select_yoshi.dat";
static const char select_803BFA70[] = "select_pacman.dat";
static const char select_803BFA84[] = "select_mspacman.dat";
static const char select_803BFA98[] = "select_monster.dat";
static const char select_803BFAAC[] = "select_waluigi.dat";
static const char select_mametch[] = "select_mametch.dat";
static const void *const selectModels[13] = {select_803BF9D0, select_803BF9E4, select_803BF9F8, select_803BFA0C, select_803BFA20, select_803BFA34, select_803BFA48, select_803BFA5C, select_803BFA70, select_803BFA84, select_803BFA98, select_803BFAAC, select_mametch};
#include "game/types/shared_data.h"
#ifndef __MWERKS__ /* the names other units use (tools/alias_census.py) */
#define destroyLog lbl_803BFB08
#endif
SHARED_STATIC const char destroyLog[] = "clCharSelTank _dt\n";
static const char createLog[] = "clCharSelTank _ct\n";

struct ModelPair {
    int id;
    clNormal3D *obj[2];
    ModelPair(int n) : id(n) {
        obj[0] = 0;
        obj[1] = 0;
        const void *desc;
        for (int i = 0; i < 2; i++) {
            desc = 0;
            int index = id;
            if (!obj[i]) {
                switch (i) {
                case 0:
                    if (!(index > -1 && index < 13)) index = 0;
                    desc = demoModels[index];
                    break;
                case 1:
                    if (!(index > -1 && index < 13)) index = 0;
                    desc = selectModels[index];
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
        DebugPrintf(createLog);
        for (int i = 0; i < 13; i++) pairs[i] = new ModelPair(i);
    }
};
extern "C" ModelBank *lbl_806D19B4;
extern "C" ModelBank *fn_801F9B64() {
    if (!lbl_806D19B4) lbl_806D19B4 = new ModelBank;
    return lbl_806D19B4;
}
