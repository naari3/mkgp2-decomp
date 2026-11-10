/* card_pack: packs the player record into the 0x45-byte card image.
 * The flag tables are written masked to 2 bits ((x == 1) & 3), which is what
 * emits the target's extrwi 2,25. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct CardPackRecord {
    u16 name[6];
    u8 volume;          /* +0x0C */
    u8 lastGetItem;     /* +0x0D */
    u16 wins;           /* +0x0E */
    u16 lose;           /* +0x10 */
    u8 pad12[2];
    int stat14;         /* +0x14 */
    u8 stat18;          /* +0x18 */
    u8 stat19;          /* +0x19 */
    u8 stat1A;          /* +0x1A */
    u8 pad1B;
    int stat1C;         /* +0x1C */
    int stat20;         /* +0x20 */
    int stat24;         /* +0x24 */
    u8 pad28[0x48 - 0x28];
    u8 flags48[8][4];   /* +0x48 */
    u8 pad68[0x88 - 0x68];
    u8 flags88[8][4];   /* +0x88 */
    u8 padA8[0x121 - 0xA8];
    u8 getItem[0x69];   /* +0x121 */
    u8 pad18A[2];
    int itemPack[3];    /* +0x18C */
    signed char remain; /* +0x198 */
    u8 update;          /* +0x199 */
    u8 missGp;          /* +0x19A */
    u8 title19B;        /* +0x19B */
    u8 title19C;        /* +0x19C */
    u8 cameraTag;       /* +0x19D */
    u8 liveTag;         /* +0x19E */
    u8 pad19F[0x1A4 - 0x19F];
    int country;        /* +0x1A4 */
    u8 pad1A8[4];
    int playCount;      /* +0x1AC */
    u8 freshCard;       /* +0x1B0 */
    u8 title1B1;        /* +0x1B1 */
    u8 pad1B2[2];
    int coinMilage;     /* +0x1B4 */
    u8 lastChara;       /* +0x1B8 */
    u8 lastKart;        /* +0x1B9 */
    u8 cupRank[3][8];   /* +0x1BA */
    u8 pad1D2[2];
    int lastClearClass; /* +0x1D4 */
    u8 lastClearUra;    /* +0x1D8 */
    u8 pad1D9;
    signed char rankin; /* +0x1DA */
} CardPackRecord;

#include "game/types/CardBitpack.h"

extern "C" {
extern void DebugPrintf(const char *, ...);
extern void *memset(void *, int, unsigned long);
extern void *memcpy(void *, const void *, unsigned long);
extern void bitpack_init(void *, void *, int, void *, u8);
extern int bitpack_get_used_bits(void *);
extern int bitpack_get_used_bytes(void *);
extern void bitpack_write_field(void *, unsigned int, const char *, int);
extern unsigned short wchar_to_card_char(const unsigned short *);
extern void calc_title_params(void *, u16 *, u8 *, u8, u8, u8);
extern const char lbl_8039C718[];
extern u8 lbl_8049B6A0[];
extern void *lbl_806D10A0;
extern int g_ccClass;
extern const signed char lbl_806DA110[1];
extern const char lbl_806DA0C0[8], lbl_806DA0C8[8], lbl_806DA0D0[7], lbl_806DA0D8[7];
extern const char lbl_806DA0E0[5], lbl_806DA0E8[6], lbl_806DA0F0[7], lbl_806DA0F8[5];
extern const char lbl_806DA100[5], lbl_806DA108[8];
}

static inline u8 CupCleared(CardPackRecord *p, int cc, int cup, int round) {
    int need;
    if (cc < 0 || cc > 2) {
        return 0;
    }
    if (cup < 1 || cup >= 17) {
        return 0;
    }
    if (cup >= 9) {
        cup -= 9;
    } else {
        cup -= 1;
    }
    need = (u8)(round + 1);
    if (round >= 4) {
        need++;
    }
    if (p->cupRank[cc][cup] >= need) {
        return 1;
    }
    return 0;
}

extern "C" int card_pack(CardPackRecord *self, u8 *out) {
    const char *messages = lbl_8039C718;
    CardBitpack pack;
    u8 buf[0x45];
    u16 title;
    u8 title2;
    int sum;
    u8 *p;
    int chara;

    DebugPrintf(messages + 0x1A60);
    if (out == 0) {
        return 0;
    }
    memset(buf, 0, 0x45);
    bitpack_init(&pack, lbl_8049B6A0, 0x49, buf, 1);
    DebugPrintf(messages + 0x1A80, bitpack_get_used_bytes(&pack), bitpack_get_used_bits(&pack));
    if (bitpack_get_used_bytes(&pack) > 0x45) {
        DebugPrintf(messages + 0x1AA0, bitpack_get_used_bytes(&pack));
        return 0;
    }
    for (int i = 0; i < 5; i++) {
        bitpack_write_field(&pack, (u8)wchar_to_card_char(&self->name[i]), lbl_806DA0E0, i);
    }
    bitpack_write_field(&pack, self->country, lbl_806DA0C8, 0);
    bitpack_write_field(&pack, self->cameraTag == 1 ? 1 : 0, messages + 0x12A4, 0);
    bitpack_write_field(&pack, self->liveTag == 1 ? 1 : 0, messages + 0x167C, 0);
    bitpack_write_field(&pack, self->remain, lbl_806DA0D0, 0);
    bitpack_write_field(&pack, self->update == 1 ? 1 : 0, lbl_806DA0D8, 0);
    chara = self->lastChara;
    chara = (signed char)chara;
    if (chara >= 13) {
        chara = 0;
    }
    bitpack_write_field(&pack, chara, messages + 0x12B0, 0);
    bitpack_write_field(&pack, self->lastKart & 1, messages + 0x12C0, 0);
    title = 0;
    title2 = 0;
    calc_title_params(lbl_806D10A0 == 0 ? 0 : lbl_806D10A0, &title, &title2, self->title19B, self->title19C,
                      self->title1B1);
    bitpack_write_field(&pack, title & 0x3FF, lbl_806DA0E8, 0);
    bitpack_write_field(&pack, title2 & 7, messages + 0x12D0, 0);
    bitpack_write_field(&pack, (title2 >> 3) & 1, messages + 0x1608, 0);
    bitpack_write_field(&pack, self->volume, lbl_806DA0F0, 0);
    bitpack_write_field(&pack, self->wins, lbl_806DA0F8, 0);
    bitpack_write_field(&pack, self->lose, lbl_806DA100, 0);
    for (int i = 0; i < 0x69; i++) {
        bitpack_write_field(&pack, self->getItem[i] == 1 ? 1 : 0, messages + 0x12DC, i);
    }
    bitpack_write_field(&pack, self->lastGetItem, messages + 0x12EC, 0);
    bitpack_write_field(&pack, self->coinMilage, messages + 0x12FC, 0);
    bitpack_write_field(&pack, self->rankin, messages + 0x1688, 0);
    for (int i = 0; i < 3; i++) {
        bitpack_write_field(&pack, self->itemPack[i], messages + 0x130C, i);
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            bitpack_write_field(&pack, self->cupRank[i][j] & 0xF,
                                ((const char *const (*)[8])(messages + 0x18F0))[i][j], 0);
        }
    }
    for (unsigned int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            bitpack_write_field(&pack, (self->flags48[i][j] == 1) & 3, ((const char *const *)(messages + 0x170C))[i], j);
        }
    }
    for (unsigned int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            bitpack_write_field(&pack, (self->flags88[i][j] == 1) & 3, ((const char *const *)(messages + 0x172C))[i], j);
        }
    }
    bitpack_write_field(&pack, self->missGp, lbl_806DA108, 0);
    bitpack_write_field(&pack, self->playCount, messages + 0x15B8, 0);
    bitpack_write_field(&pack, self->stat14, messages + 0x15C8, 0);
    bitpack_write_field(&pack, self->stat18, messages + 0x15D8, 0);
    bitpack_write_field(&pack, self->stat19, messages + 0x15E8, 0);
    bitpack_write_field(&pack, self->stat1A == 1 ? 1 : 0, messages + 0x15F8, 0);
    bitpack_write_field(&pack, self->stat1C, messages + 0x1618, 0);
    bitpack_write_field(&pack, self->stat20, messages + 0x1628, 0);
    bitpack_write_field(&pack, self->stat24, messages + 0x1638, 0);
    int count = 0;
    for (int cup = 1; cup < 8; cup++) {
        if (CupCleared(self, g_ccClass, cup, 0) == 1) {
            count++;
        }
    }
    if (count > 0) {
        bitpack_write_field(&pack, self->lastClearClass, messages + 0x1648, 0);
        bitpack_write_field(&pack, self->lastClearUra != 0, messages + 0x1664, 0);
    }
    for (int i = 0; i < 3; i++) {
        bitpack_write_field(&pack, lbl_806DA110[i], messages + 0x128C, i);
    }
    if (self->freshCard == 0) {
        bitpack_write_field(&pack, 2, lbl_806DA0C0, 0);
    } else {
        bitpack_write_field(&pack, 0, lbl_806DA0C0, 0);
    }
    self->freshCard = 0;
    bitpack_write_field(&pack, 0, messages + 0x1298, 0);
    sum = 0;
    p = buf;
    for (int i = 0; i < 0x45; i++) {
        sum += *p++;
    }
    bitpack_write_field(&pack, sum & 0xFF, messages + 0x1298, 0);
    memcpy(out, buf, 0x45);
}
