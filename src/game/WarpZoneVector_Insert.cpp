/*
 * WarpZoneVector (0x800A9D84..0x800AA888): std::vector<WarpZoneValue>
 * insert/reserve and their helpers in one TU, so the length_error
 * type string lbl_803284C0 has a single owner.
 * -inline noauto,deferred emits the functions in reverse source order,
 * so they are written from the last address to the first.
 */
extern "C" {
unsigned long strlen(const char *);
char *strcpy(char *, const char *);
void *FUN_8003b120(unsigned long);
void *Alloc(unsigned long);
void MemoryManager_TimedFree(void *);
extern const char lbl_803284A4[];
extern const char WarpZoneVector_Reserve_rodata_803284F8[];
}
inline void *operator new(unsigned long, void *p) { return p; }
inline void operator delete(void *, void *) {}

/* Four corners have nontrivial lifetime; the two remaining vectors are plain. */
#include "game/types/WarpPlainVector.h"
#include "game/types/WarpCorner.h"
#include "game/types/WarpZoneValue.h"
inline void *operator new(unsigned long, WarpZoneValue *p) throw() { return p; }
inline void operator delete(void *, WarpZoneValue *) throw() {}

#include "game/types/WarpErrorString.h"
struct WarpString {
    WarpErrorString storage;
    ~WarpString();
    WarpString(const char *s) : storage(FUN_8003b120(strlen(s) + 1)) { strcpy(storage.ptr, s); }
};
namespace std {
struct exception { exception() {} virtual ~exception(); };
struct logic_error : exception {
    WarpString message;
    logic_error(const char *s) : message(s) {}
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
WarpZoneValue *WarpZone_OperatorAssign_LinkerStub(WarpZoneValue *, const WarpZoneValue *);
WarpZoneValue *WarpZoneArray_CopyBackwardImpl(WarpZoneValue *, WarpZoneValue *, WarpZoneValue *);
}

extern "C" WarpZoneValue *WarpZone_OperatorAssign_LinkerStub(WarpZoneValue *p, const WarpZoneValue *value) {
    return WarpZone_OperatorAssign_LinkerStub(p, value);
}
extern "C" WarpZoneValue *WarpZoneArray_CopyBackwardImpl(WarpZoneValue *first, WarpZoneValue *last, WarpZoneValue *out) {
    while (last > first) { --out; --last; WarpZone_OperatorAssign_LinkerStub(out, last); }
    return out;
}
extern "C" WarpZoneValue *WarpZoneArray_CopyBackward(WarpZoneValue *first, WarpZoneValue *last, WarpZoneValue *out) {
    return WarpZoneArray_CopyBackwardImpl(first, last, out);
}
extern "C" void WarpZoneArray_UninitFillN(WarpZoneValue *p, unsigned long n, const WarpZoneValue *value) {
    for (; n != 0; ++p, --n) WarpZone_OperatorAssign_LinkerStub(p, value);
}
extern "C" void WarpZoneVector_Clear(WarpZoneVectorStorage *s) {
    WarpZoneValue *first = s->data;
    WarpZoneValue *p = first + s->count;
    while (p > first) (--p)->~WarpZoneValue();
    s->count = 0;
}
#pragma auto_inline on
WarpZoneVectorStorage::~WarpZoneVectorStorage() {
    WarpZoneVector_Clear(this);
    if (data) MemoryManager_TimedFree(data);
}
#pragma auto_inline off
extern "C" void WarpZoneVector_Reserve(WarpZoneVectorStorage *s, unsigned long n) {
    if (n > s->capacity) {
        if (n > 0x03333333) throw std::length_error(WarpZoneVector_Reserve_rodata_803284F8);
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
extern "C" void WarpZoneVector_Insert(WarpZoneVectorStorage *s, WarpZoneValue *position,
                                      unsigned long n, const WarpZoneValue *value) {
    if (n != 0) {
        if (n > 0x03333333 || s->count > 0x03333333 - n)
            throw std::length_error(lbl_803284A4);
        unsigned long newCount = s->count + n;
        if (newCount <= s->capacity) {
            WarpZoneValue *end = s->data + s->count;
            unsigned long tail = end - position;
            if (n > tail) {
                WarpZoneValue *out = end;
                for (; n > tail; ++out, --n, ++s->count)
                    new ((void *)out) WarpZoneValue(*value);
                for (WarpZoneValue *p = position; p < end; ++p, ++out, ++s->count)
                    new ((void *)out) WarpZoneValue(*p);
            } else {
                WarpZoneValue *p = end - n;
                WarpZoneValue *out = end;
                for (; p < end; ++p, ++out, ++s->count)
                    new ((void *)out) WarpZoneValue(*p);
                if (end - (tail - n) <= value && value < end) value += n;
                WarpZoneArray_CopyBackward(position, position + (tail - n), end);
            }
            WarpZoneArray_UninitFillN(position, n, value);
        } else {
            WarpZoneVectorStorage temp;
            unsigned long capacity = s->capacity ? s->capacity : 1;
            while (newCount > capacity) {
                if (capacity < 0x01999999) capacity *= 2;
                else capacity = 0x03333333;
            }
            temp.data = (WarpZoneValue *)Alloc(capacity * sizeof(WarpZoneValue));
            temp.capacity = capacity;
            WarpZoneValue *end = s->data + s->count;
            WarpZoneValue *out = temp.data;
            WarpZoneValue *p = s->data;
            for (; p < position; ++p, ++out, ++temp.count)
                new ((void *)out) WarpZoneValue(*p);
            for (; n != 0; ++out, --n, ++temp.count)
                new ((void *)out) WarpZoneValue(*value);
            for (; p < end; ++p, ++out, ++temp.count)
                new ((void *)out) WarpZoneValue(*p);
            temp.swap(*s);
        }
    }
}
