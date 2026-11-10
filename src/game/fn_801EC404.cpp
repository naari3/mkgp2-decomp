/* Destructor of a path owner subclass (base destructor inlined). */
extern "C" {
extern void *lbl_804E4BEC[];
extern void *lbl_804E4C18[];
}

#include "game/types/PathUser.h"

#include "game/types/PathUserHolder.h"

#include "game/types/PathOwner.h"

struct PathOwner801EC404 : PathOwner {
    ~PathOwner801EC404();
};

PathOwner801EC404::~PathOwner801EC404() {
    vt = lbl_804E4BEC;
}
