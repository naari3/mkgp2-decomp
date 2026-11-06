#include "game/anon_80224ECC_private.h"

clCSSceneBanner::~clCSSceneBanner() {
    fn_80169C44();
    SpriteHandle_Destroy(fade);
    if (obj) {
        delete obj;
        obj = 0;
    }
    DeleteSprite(spr);
}
