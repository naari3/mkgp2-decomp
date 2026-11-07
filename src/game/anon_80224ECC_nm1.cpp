#include "game/anon_80224ECC_private.h"

clCSSceneBanner::~clCSSceneBanner() {
    fn_80169C44();
    SpriteHandle_Destroy(fade);
    if (obj) {
        delete obj;
        obj = 0;
    }
    /* fakematch (permuter): a one-trip loop hoists the 0 store into r31 ahead
     * of the null test, as in the target. Natural code: DeleteSprite(spr); */
    for (int i = 0; i < 1; i++) {
        DeleteSprite(spr);
    }
}
