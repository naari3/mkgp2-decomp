#ifndef GAME_TYPES_KARTDRIVER_H
#define GAME_TYPES_KARTDRIVER_H

struct HSD_JObj;
struct ItemEffectBus;
struct KartHelper;

/* Merged from 21 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct KartDriver KartDriver;
struct KartDriver {
    /* 0x000 */ void *model;
    /* 0x004 */ void *lodMid;
    /* 0x008 */ void *lodFar;
    /* 0x00C */ void *driver;
    /* 0x010 */ void *obj10;
    /* 0x014 */ void *obj14;
    /* 0x018 */ void *obj18;
    /* 0x01C */ void *accessory;
    /* 0x020 */ void *extra;
    /* 0x024 */ void *parts[49];
    /* 0x0E8 */ struct HSD_JObj *wheel[4];
    /* 0x0F8 */ unsigned char pad_0F8[0x58];
    /* 0x150 */ void *extraEnabled;
    /* 0x154 */ unsigned char pad_154[0x10];
    /* 0x164 */ struct HSD_JObj *joint164;
    /* 0x168 */ struct HSD_JObj *joint_168;
    /* 0x16C */ struct HSD_JObj *joint16C;
    /* 0x170 */ float baseRotZ;
    /* 0x174 */ unsigned char showAccessory;
    /* 0x175 */ unsigned char pad_175[0x7];
    /* 0x17C */ void *matrixSource;
    /* 0x180 */ unsigned char pad_180[0x68];
    /* 0x1E8 */ int visible;
    /* 0x1EC */ unsigned char pad_1EC[0x54];
    /* 0x240 */ int lap;
    /* 0x244 */ unsigned char pad_244[0x4];
    /* 0x248 */ void *raceSlot;
    /* 0x24C */ unsigned char pad_24C[0x50];
    /* 0x29C */ void *obj29C;
    /* 0x2A0 */ unsigned char pad_2A0[0x30];
    /* 0x2D0 */ unsigned char forceDraw;
    /* 0x2D1 */ unsigned char pad_2D1[0xB];
    /* 0x2DC */ void *seSlots[10];
    /* 0x304 */ struct ItemEffectBus *itemBus;
    /* 0x308 */ unsigned char pad_308[0x4];
    /* 0x30C */ void *tireFX;
    /* 0x310 */ unsigned char pad_310[0x1C];
    /* 0x32C */ void *buf32C;
    /* 0x330 */ unsigned char pad_330[0x14];
    /* 0x344 */ void *buf344;
    /* 0x348 */ unsigned char pad_348[0x14];
    /* 0x35C */ struct KartHelper *helper35C;
    /* 0x360 */ struct KartHelper *helper360;
    /* 0x364 */ unsigned char pad_364[0x14];
    /* 0x378 */ struct KartHelper *helper378;
    /* 0x37C */ unsigned char pad_37C[0x4];
    /* 0x380 */ struct KartHelper *helper380;
};

#endif /* GAME_TYPES_KARTDRIVER_H */
