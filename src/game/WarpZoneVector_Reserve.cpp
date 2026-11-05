#pragma exceptions on
#include "game/WarpReservePrivate.h"
extern "C" const char lbl_803284F8[];
extern "C" WarpZoneValue *WarpZone_OperatorAssign_LinkerStub(WarpZoneValue *, const WarpZoneValue *);
extern "C" WarpZoneValue *WarpZoneArray_CopyBackwardImpl(WarpZoneValue *, WarpZoneValue *, WarpZoneValue *);
extern "C" void WarpZoneVector_Reserve(WarpZoneVectorStorage *s, unsigned long n) {
    if (n > s->capacity) {
        if (n > 0x03333333) throw std::length_error(lbl_803284F8);
        WarpZoneVectorStorage temp;
        temp.data = (WarpZoneValue *)Alloc(n * sizeof(WarpZoneValue));
        temp.capacity = n;
        WarpZoneValue *end = s->data + s->count;
        WarpZoneValue *out = temp.data;
        for (WarpZoneValue *p = s->data; p < end; ++p, ++out, ++temp.count)
            new (out) WarpZoneValue(*p);
        temp.swap(*s);
    }
}
extern "C" void WarpZoneVector_Clear(WarpZoneVectorStorage *s) {
    WarpZoneValue *first = s->data;
    WarpZoneValue *p = first + s->count;
    while (p > first) (--p)->~WarpZoneValue();
    s->count = 0;
}
extern "C" void WarpZoneArray_UninitFillN(WarpZoneValue *p, unsigned long n, const WarpZoneValue *value) {
    for (; n != 0; ++p, --n) WarpZone_OperatorAssign_LinkerStub(p, value);
}
extern "C" WarpZoneValue *WarpZoneArray_CopyBackward(WarpZoneValue *first, WarpZoneValue *last, WarpZoneValue *out) {
    return WarpZoneArray_CopyBackwardImpl(first, last, out);
}
extern "C" WarpZoneValue *WarpZoneArray_CopyBackwardImpl(WarpZoneValue *first, WarpZoneValue *last, WarpZoneValue *out) {
    while (last > first) { --out; --last; WarpZone_OperatorAssign_LinkerStub(out, last); }
    return out;
}
extern "C" WarpZoneValue *WarpZone_OperatorAssign_LinkerStub(WarpZoneValue *p, const WarpZoneValue *value) {
    return WarpZone_OperatorAssign_LinkerStub(p, value);
}
