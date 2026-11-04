#ifndef MKGP2_STATE_PRIVATE_H
#define MKGP2_STATE_PRIVATE_H
#include "state.h"
struct matstate_t {
    GXColor ambient;
    GXColor diffuse;
    GXColor specular;
    u8 alpha;
    f32 shininess;
};
extern struct matstate_t matstate;
#endif
