#include "game/anon_80218F40_private.h"

#pragma push
#pragma opt_common_subs off
MinimapHud::~MinimapHud() {
    MinimapHud *cursor = this;
    int i;
    for (i = 0; i < 11; i++) {
        SpriteHandle_Destroy(cursor->sprites[0]);
        cursor = (MinimapHud *)((char *)cursor + sizeof(int));
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
    for (int j = 0; j < 4; j++) {
        fn_80120A08(j + 0xBCD);
    }
}
#pragma pop

