/* Manager destructor, 0x8005F65C..0x8005F778. */
#include "game/clItemBoxManagerPrivate.h"

clItemBoxManager::~clItemBoxManager()
{
    ListIter<void *> it;
    for (it = boxes.begin(); it != boxes.end(); ++it) {
        clItemBox_Dtor(*it, 1);
    }
    clItemBoxManager_TeardownAssets();
    fn_8016CB4C();
}
