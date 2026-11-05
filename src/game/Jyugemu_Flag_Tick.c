#pragma cplusplus on
#include "game/JyugemuFlagTickPrivate.h"

#pragma exceptions on
inline int Flag::Tick() {
    FlagDesc *desc;
    float (*matrix)[4];
    if (!this->object) return 0;
    if (!this->driver) return 0;
    desc = this->desc;
    matrix = KartDriver_GetKartRootMtx(this->driver);
    SetX(Archive_GetRootJObj(this->object), desc->x + matrix[0][3]);
    SetY(Archive_GetRootJObj(this->object), desc->y + matrix[1][3]);
    SetZ(Archive_GetRootJObj(this->object), desc->z + matrix[2][3]);
    RotateY(Archive_GetRootJObj(this->object), lbl_806D3070 * this->desc->angle);
    clNormal3D_Exec(this->object);
    Object_DriveAnimMatrix(this->object);
    return 1;
}
extern "C" int Jyugemu_Flag_Tick(Flag *self) { return self->Tick(); }
#pragma exceptions reset

#pragma cplusplus reset
