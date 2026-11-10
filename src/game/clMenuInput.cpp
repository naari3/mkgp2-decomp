/* clMenuInput, 0x80073E20..0x80073F6C.
 *
 * `clMenuInput : teSingleton<clMenuInput>` (names from the game's RTTI,
 * tools/rtti_classes.py). The compiler emits both vtables, the RTTI records
 * and the class-name strings. The other functions of the original file are
 * the small menu entry points below. Units that construct the singleton
 * still store the two tables by hand under their symbols.txt names. */
#include "game/types/size_t.h"

void *operator new(size_t);
void operator delete(void *) throw();

extern "C" {
void ServiceButtonExtra_Set(unsigned char value);
void SetSyncTarget(int target);
void Sci2Card_PrintReceipt_StartFlow(int, int, int);
}

template <class T> struct teSingleton {
    virtual ~teSingleton() {}
};

class clMenuInput : public teSingleton<clMenuInput> {
public:
    virtual ~clMenuInput();
};

struct ServiceMenu {
    unsigned char opaque[0x28C];
    ServiceMenu(int param);
};

clMenuInput::~clMenuInput() {}

extern "C" void *OpenFullServiceMenu(void)
{
    ServiceButtonExtra_Set(1);
    SetSyncTarget(0x35);
    return new ServiceMenu(-1);
}

extern "C" void PostRace_StartScoreEntryFlow(void)
{
    Sci2Card_PrintReceipt_StartFlow(3, 1, 0);
}

extern "C" void PostRace_StartScoreEntryFlow_WithCardSave(void)
{
    Sci2Card_PrintReceipt_StartFlow(3, 1, 1);
}
