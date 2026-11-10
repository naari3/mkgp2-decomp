#ifndef GAME_TYPES_KARTDRIVER_H
#define GAME_TYPES_KARTDRIVER_H

struct Accessory;
struct DriverTail;
struct EffectState;
struct HSD_JObj;
struct ItemEffectBus;
struct KartHelper;
struct Normal3D;
struct TireFX;

/* Merged from 53 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct KartDriver KartDriver;
struct KartDriver {
    /* 0x000 */ struct Normal3D *model;  /* also: kart */
    /* 0x004 */ struct Normal3D *lodMid;  /* also: wheelA */
    /* 0x008 */ struct Normal3D *lodFar;  /* also: wheelB */
    /* 0x00C */ struct Normal3D *driver;  /* also: character */
    /* 0x010 */ struct Normal3D *animation;
    /* 0x014 */ struct Normal3D *other;
    /* 0x018 */ struct Normal3D *obj18;  /* also: shadow */
    /* 0x01C */ struct Normal3D *accessory;
    /* 0x020 */ struct Normal3D *extra;
    /* 0x024 */ struct Normal3D *parts[49];  /* also: slots */
    /* 0x0E8 */ struct HSD_JObj *wheel[4];  /* also: tires */
    /* 0x0F8 */ void *ground[4];
    /* 0x108 */ void *joint108;
    /* 0x10C */ void *engine;
    /* 0x110 */ void *body;
    /* 0x114 */ void *mufflerL;
    /* 0x118 */ void *mufflerR;
    /* 0x11C */ void *handNull;
    /* 0x120 */ void *teresa;
    /* 0x124 */ void *info;
    /* 0x128 */ void *head;
    /* 0x12C */ void *a12C;
    /* 0x130 */ void *handGoo;
    /* 0x134 */ void *handPa;
    /* 0x138 */ void *a138;
    /* 0x13C */ void *joint13C;
    /* 0x140 */ void *joint140;
    /* 0x144 */ void *joint144;
    /* 0x148 */ void *joint148;
    /* 0x14C */ void *joint14C;
    /* 0x150 */ void *extraEnabled;  /* also: joint150 */
    /* 0x154 */ void *joint154;
    /* 0x158 */ void *joint158;
    /* 0x15C */ void *joint15C;
    /* 0x160 */ void *joint160;
    /* 0x164 */ struct HSD_JObj *joint164;
    /* 0x168 */ struct HSD_JObj *joint_168;  /* also: joint168 */
    /* 0x16C */ struct HSD_JObj *joint16C;
    /* 0x170 */ float baseRotZ;
    /* 0x174 */ unsigned char showAccessory;
    /* 0x175 */ unsigned char pad_175[0x3];
    /* 0x178 */ int a178;
    /* 0x17C */ void *matrixSource;  /* also: matrix */
    /* 0x180 */ unsigned char pad_180[0x68];
    /* 0x1E8 */ int visible;
    /* 0x1EC */ unsigned char pad_1EC[0x4];
    /* 0x1F0 */ long currentState;
    /* 0x1F4 */ int slot;  /* also: eventType, id */
    /* 0x1F8 */ int chara;  /* also: characterId, chr, kind */
    /* 0x1FC */ unsigned char pad_1FC[0x8];
    /* 0x204 */ unsigned char flag204;
    /* 0x205 */ unsigned char pad_205[0x13];
    /* 0x218 */ int contextSlot;
    /* 0x21C */ unsigned char pad_21C[0x10];
    /* 0x22C */ int a22C;
    /* 0x230 */ unsigned char pad_230[0x8];
    /* 0x238 */ int visible_238;  /* also: enabled, visible, wingEnabled */
    /* 0x23C */ int airState;  /* also: slot */
    /* 0x240 */ int lap;
    /* 0x244 */ unsigned char pad_244[0x4];
    /* 0x248 */ void *raceSlot;  /* also: link, slot */
    /* 0x24C */ int a24C;
    /* 0x250 */ unsigned char pad_250[0x4C];
    /* 0x29C */ struct Accessory *driver_29C;  /* also: accessory, driver */
    /* 0x2A0 */ unsigned char pad_2A0[0x11];
    /* 0x2B1 */ unsigned char noItems;
    /* 0x2B2 */ unsigned char pad_2B2[0xE];
    /* 0x2C0 */ long currentItemId;
    /* 0x2C4 */ unsigned char pad_2C4[0x8];
    /* 0x2CC */ int coins;  /* also: section */
    /* 0x2D0 */ unsigned char forceDraw;  /* also: mode2Enabled, sound, special, startSlot */
    /* 0x2D1 */ unsigned char pad_2D1[0xB];
    /* 0x2DC */ void *seSlots[10];
    /* 0x304 */ struct ItemEffectBus *itemBus;  /* also: effects, state, status */
    /* 0x308 */ unsigned char pad_308[0x4];
    /* 0x30C */ struct TireFX *tireFX;
    /* 0x310 */ unsigned char pad_310[0x8];
    /* 0x318 */ float a318;
    /* 0x31C */ float a31C;
    /* 0x320 */ float a320;
    /* 0x324 */ float a324;
    /* 0x328 */ float a328;
    /* 0x32C */ struct EffectState *a32C;
    /* 0x330 */ unsigned char pad_330[0x8];
    /* 0x338 */ float velocity[3];
    /* 0x344 */ struct DriverTail *tail;
    /* 0x348 */ unsigned char pad_348[0x14];
    /* 0x35C */ struct KartHelper *helper35C;
    /* 0x360 */ struct KartHelper *helper360;
    /* 0x364 */ unsigned char pad_364[0x4];
    /* 0x368 */ unsigned char a368;
    /* 0x369 */ unsigned char pad_369[0xB];
    /* 0x374 */ int a374;
    /* 0x378 */ struct KartHelper *helper378;
    /* 0x37C */ unsigned char pad_37C[0x4];
    /* 0x380 */ struct KartHelper *helper380;
};

#endif /* GAME_TYPES_KARTDRIVER_H */
