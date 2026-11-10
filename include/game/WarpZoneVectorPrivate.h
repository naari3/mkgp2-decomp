#ifndef GAME_WARP_ZONE_VECTOR_PRIVATE_H
#define GAME_WARP_ZONE_VECTOR_PRIVATE_H
#include "game/types/size_t.h"

extern "C" {
unsigned long strlen(const char *);
char *strcpy(char *, const char *);
void *FUN_8003b120(unsigned long);
void *Alloc(unsigned long);
void MemoryManager_TimedFree(void *);
extern const char lbl_803284A4[];
}
inline void *operator new(size_t, void *p) { return p; }

/* Four corners have nontrivial lifetime; the two remaining vectors are plain. */
#include "game/types/WarpPlainVector.h"
#include "game/types/WarpCorner.h"
#include "game/types/WarpZoneValue.h"

#include "game/types/WarpErrorString.h"
namespace std {
struct exception { exception() {} virtual ~exception(); };
struct logic_error : exception {
    WarpErrorString message;
    logic_error(const char *s) : message(FUN_8003b120(strlen(s) + 1)) {
        strcpy(message.ptr, s);
    }
    virtual ~logic_error();
};
struct length_error : logic_error {
    length_error(const char *s) : logic_error(s) {}
    virtual ~length_error();
};
}

#include "game/types/WarpZoneVectorStorage.h"
extern "C" {
void WarpZoneVector_Clear(WarpZoneVectorStorage *);
void WarpZoneArray_UninitFillN(WarpZoneValue *, unsigned long, const WarpZoneValue *);
WarpZoneValue *WarpZoneArray_CopyBackward(WarpZoneValue *, WarpZoneValue *, WarpZoneValue *);
}
inline WarpZoneVectorStorage::~WarpZoneVectorStorage() {
    WarpZoneVector_Clear(this);
    if (data) MemoryManager_TimedFree(data);
}

#endif
