#ifndef TRIFORCE_DVDLOW_PRIVATE_H
#define TRIFORCE_DVDLOW_PRIVATE_H
#include <dolphin/types.h>

typedef struct DIKey {
    u32 cmd;
    u32 offset;
    u32 length;
} DIKey;

extern DIKey* __DIKey;
void fn_8028625C(u32 cmd, u32 offset, u32 length);
#endif
