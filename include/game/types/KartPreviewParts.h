#ifndef GAME_TYPES_KARTPREVIEWPARTS_H
#define GAME_TYPES_KARTPREVIEWPARTS_H

typedef struct KartPreviewParts {
    void *kart;
    void *tires;
    void *driver;
    void *extraA;
    void *extraB;
    void *parts[49];
    int fD8;
    float fDC[3];
    int characterId;
    int animCur;
    int animNext;
    int animBase;
    float fF8;
    float fFC;
    float f100;
    int f104;
    float f108;
    float f10C;
    float f110;
    float f114;
    float f118;
    float f11C;
    float f120;
    void *attach;
    void *attachJoint;
    char pad12C[0x144 - 0x12C];
    int f144;
    int f148;
    int f14C;
    int f150;
    int f154;
    int f158;
    int f15C;
    int f160;
    int f164;
} KartPreviewParts;

#endif /* GAME_TYPES_KARTPREVIEWPARTS_H */
