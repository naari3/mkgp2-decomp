#include "game/anon_80218F40_private.h"

MinimapHud::~MinimapHud() {
    int i;
    for (i = 0; i < 11; i++) {
        SpriteHandle_Destroy(sprites[i]);
    }
    delete[] order;
    fn_80120A08(resId);
    switch (CupIndex()) {
    case 4:
        fn_80120A08(0xC14);
        break;
    case 6:
        fn_80120A08(0xC16);
        break;
    }
    fn_80120A08(0xBCC);
    fn_80120A08(0xBD2);
    fn_80120A08(0xBD1);
    for (i = 0; i < 4; i++) {
        fn_80120A08(i + 0xBCD);
    }
}
