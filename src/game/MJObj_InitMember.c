/* MJObj member init: run the parent class init, then default the RGBA
 * colour to opaque white. */
#include "game/types/MJObj.h"

typedef struct MJObjClassInfo {
    unsigned char pad00[0x2c];
    int (*member_init)(MJObj *self);
} MJObjClassInfo;

extern MJObjClassInfo hsdJObj;

int MJObj_InitMember_RGBA(MJObj *self)
{
    int ret = hsdJObj.member_init(self);

    if (ret != 0) {
        return ret;
    }
    self->rgba[0] = 0xff;
    self->rgba[1] = 0xff;
    self->rgba[2] = 0xff;
    self->rgba[3] = 0xff;
    return 0;
}
