#include "game/types/c_region.h"
C_REGION_BEGIN
/* Arm the responder's command timer and fetch the world position through
 * its vtable. */
C_REGION_END
#pragma cplusplus on

class clItemBoxResponder {
public:
    virtual void GetWorldPos();

    void *boundPos; /* 0x04 */
    int cmdTimer;   /* 0x08 */
};

extern "C" void clItemBoxResponder_CmdGetWorldPos(clItemBoxResponder *self)
{
    self->cmdTimer = 0x3c;
    self->GetWorldPos();
}

#pragma cplusplus reset
