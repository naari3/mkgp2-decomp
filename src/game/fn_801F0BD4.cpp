/* Destructor of a path owner subclass (base destructor inlined). */
extern "C" {
extern void *lbl_804E4C08[];
extern void *lbl_804E4C18[];
}

#include "game/types/PathUser.h"

#include "game/types/PathUserHolder.h"

#include "game/types/PathOwner.h"

struct PathOwner801F0BD4 : PathOwner {
    ~PathOwner801F0BD4();
};

PathOwner801F0BD4::~PathOwner801F0BD4() {
    vt = lbl_804E4C08;
}
