#include "game/ItemListHudPrivate.h"
ItemListHud::~ItemListHud() {
    for (int i=7; i>=0; --i) {
        if (objects[i]) { delete objects[i]; objects[i]=0; }
        values[i]=0;
    }
}
