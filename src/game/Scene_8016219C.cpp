#include "game/Scene_8016219CPrivate.h"

extern "C" void fn_8016219C(PointerTable162 *s, unsigned long n, void *const &value) {
    if (n != 0) {
        if (n > 0x3fffffff) throw std::length_error(lbl_80369238);
        s->data = (void **)Alloc(n * sizeof(void *));
        void *v = value;
        s->count = n;
        s->capacity = n;
        void **p = s->data;
        for (unsigned long i = n; i != 0; --i) *p++ = v;
    }
}
