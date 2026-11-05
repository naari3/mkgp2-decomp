#ifndef BOOT_DISPATCHER_PRIVATE_H
#define BOOT_DISPATCHER_PRIVATE_H

struct Word2 {
    unsigned int w[2];
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
    Word2 f18;
    Word2 f20;
    unsigned int f28;
    Word2 f2C;
    Word2 f34;
    unsigned int f3C;
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
        f20 = o.f20;
        f28 = o.f28;
        f2C = o.f2C;
        f34 = o.f34;
        f3C = o.f3C;
        f40 = o.f40;
        f48 = o.f48;
        f50 = o.f50;
        f58 = o.f58;
        f5C = o.f5C;
        return *this;
    }
};

struct BootTimer {
    unsigned int lastTick;
};

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
struct BootColor { unsigned char r,g,b,a; };
struct BootVI { unsigned char pad00[0x48]; BootColor color; };
#endif
