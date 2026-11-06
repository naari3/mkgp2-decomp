#include "game/WarpZoneInsertPrivate.h"

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
                    new (out) WarpZoneValue(*value);
                for (WarpZoneValue *p = position; p < end; ++p, ++out, ++s->count)
                    new (out) WarpZoneValue(*p);
            } else {
                WarpZoneValue *p = end - n;
                WarpZoneValue *out = end;
                for (; p < end; ++p, ++out, ++s->count)
                    new (out) WarpZoneValue(*p);
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
                new (out) WarpZoneValue(*p);
            for (; n != 0; ++out, --n, ++temp.count)
                new (out) WarpZoneValue(*value);
            for (; p < end; ++p, ++out, ++temp.count)
                new (out) WarpZoneValue(*p);
            temp.swap(*s);
        }
    }
}
