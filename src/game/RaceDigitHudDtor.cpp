#include "game/RaceDigitHudDtorPrivate.h"

RaceDigitHudDtor::~RaceDigitHudDtor() {
    for (int i = 0; i < 4; ++i) SpriteHandle_Destroy(sprites[i]);
    RaceDigitIterator end(list.End());
    RaceDigitIterator begin(list.first);
    fn_80247B8C(&list, begin, end);
}
