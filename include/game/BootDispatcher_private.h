#ifndef BOOT_DISPATCHER_PRIVATE_H
#define BOOT_DISPATCHER_PRIVATE_H

#include "game/types/Word2.h"

struct Word5 {
    Word2 a;
    Word2 b;
    unsigned int c;

    Word5 &operator=(const Word5 &o)
    {
        Word5 *d = this;
        d->a = o.a;
        d->b = o.b;
        d->c = o.c;
        return *this;
    }
};

struct BootState {
    unsigned short f00;
    unsigned short f02;
    unsigned short f04;
    unsigned short f06;
    Word2 f08;
    unsigned char f10;
    unsigned char f11;
    unsigned short f12;
    unsigned short f14;
    unsigned short f16;
    Word5 f18;
    Word5 f2C;
    Word2 f40;
    Word2 f48;
    Word2 f50;
    unsigned int f58;
    unsigned int f5C;

    BootState &operator=(const BootState &o)
    {
        f00 = o.f00;
        f02 = o.f02;
        f04 = o.f04;
        f06 = o.f06;
        f08 = o.f08;
        f10 = o.f10;
        f11 = o.f11;
        f12 = o.f12;
        f14 = o.f14;
        f16 = o.f16;
        f18 = o.f18;
        f2C = o.f2C;
        f40 = o.f40;
        f48 = o.f48;
        f50 = o.f50;
        f58 = o.f58;
        f5C = o.f5C;
        return *this;
    }
};

#include "game/types/BootTimer.h"

struct BootConfig {
    unsigned char pad00[0x21];
    signed char effect, intensity;
    unsigned char card, cardDisabled, otherDisabled;
    unsigned char pad26[4];
    unsigned char skipNotice, pad2B, volume, effectsVolume, soundMode, pad2F, soundOption;
    unsigned char pad31[3];
    int steering, position, brake, accel;
    unsigned char pad44[0x22C];
    unsigned char receiptTest;
};
struct BootError {
    unsigned char code[3]; unsigned char pad03;
    unsigned int pad04, enabled;
    unsigned char pad0C[12];
};
struct BootHook { virtual void unused(); virtual void Tick(); };
struct BootHooks { BootHook *begin, *end; };
#include "game/types/BootColor.h"
struct BootVI { unsigned char pad00[0x48]; BootColor color; };
#endif
