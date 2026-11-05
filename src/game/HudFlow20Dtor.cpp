#include "game/HudFlow20Private.h"
extern "C" {
void fn_80120A08(int);
void SpriteHandle_Destroy(void *);
}
HudFlow20::~HudFlow20() {
    fn_80120A08(0xc29);
    SpriteHandle_Destroy(sprite);
}
