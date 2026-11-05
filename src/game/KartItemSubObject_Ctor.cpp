#include "game/C7ItemCtorPrivate.h"
C7ItemOwners::C7ItemOwners(void* car) : kart(car),
    impact((C7Effect<0>*)new C7Impact(this)),
    quake((C7Effect<1>*)new C7Quake(this)),
    jump((C7Effect<2>*)new C7Jump(this)),
    damp((C7Effect<3>*)new C7Damp(this)),
    spin((C7Effect<4>*)new C7Spin(this)) {
    state=0;
}
