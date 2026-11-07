/* card_unpack: restores the player record from an unpacked card bitpack. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct CardUnpackRecord {
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
    u8 unlockFlags[0x79]; /* +0xA8 */
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
    signed char lastChara; /* +0x1B8 */
    signed char lastKart;  /* +0x1B9 */
    u8 cupRank[3][8];   /* +0x1BA */
    u8 pad1D2[2];
    int lastClearClass; /* +0x1D4 */
    u8 lastClearUra;    /* +0x1D8 */
    u8 pad1D9;
    signed char rankin; /* +0x1DA */
} CardUnpackRecord;

typedef struct ItemUnlockEntry {
    int pad0;
    int unlock;
    int item;
    int pad0C[2];
} ItemUnlockEntry;

extern "C" {
extern void DebugPrintf(const char *, ...);
extern void *memset(void *, int, unsigned long);
extern void bitpack_read_field_by_name(void *, const char *, unsigned int *, int);
extern int isJapanese(void);
extern void fn_801D7610(void *, u8);
extern u16 fn_801F8DB0(u8);
extern u8 NameCheck_CardName(const u16 *);
extern void TitleDecode(void *, u8 *, u8 *, u8 *, u16, u8);
extern void SetKartVariant(int);
extern const char lbl_8039C718[];
extern void *lbl_806D10A0;
extern int g_characterId;
extern u8 lbl_806D12E4[3];
extern const char lbl_806DA0C8[8], lbl_806DA0D0[7], lbl_806DA0D8[7];
extern const char lbl_806DA0E0[5], lbl_806DA0E8[6], lbl_806DA0F0[7], lbl_806DA0F8[5];
extern const char lbl_806DA100[5], lbl_806DA108[8];
}

static inline u8 RankReached(CardUnpackRecord *p, int cc, int cup, int round) {
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

static inline u8 AllCupsCleared(CardUnpackRecord *p, int cc) {
    u8 ok = 1;
    for (int cup = 1; cup < 9; cup++) {
        if (cup == 6) {
            continue;
        }
        if (!RankReached(p, cc, cup, 3)) {
            ok = 0;
            break;
        }
    }
    return ok;
}

extern "C" u8 card_unpack(CardUnpackRecord *self, void *pack, u8 publish) {
    const char *messages = lbl_8039C718;
    unsigned int country;
    unsigned int ch;
    unsigned int value;
    unsigned int title;
    unsigned int titleParam;
    unsigned int titleParam2;
    unsigned int rank;
    unsigned int stat14;
    unsigned int stat18;
    unsigned int stat19;
    unsigned int stat1A;
    unsigned int stat1C;
    unsigned int stat20;
    unsigned int stat24;
    unsigned int flag;
    unsigned int getItem;
    unsigned int itemPack;
    unsigned int missGp;
    unsigned int playCount;
    unsigned int clear;

    country = 0;
    bitpack_read_field_by_name(pack, lbl_806DA0C8, &country, 0);
    if (country != isJapanese()) {
        return 0;
    }
    fn_801D7610(self, 0);
    memset(self, 0, 12);
    for (int i = 0; i < 5; i++) {
        bitpack_read_field_by_name(pack, lbl_806DA0E0, &ch, i);
        self->name[i] = fn_801F8DB0((u8)ch);
    }
    if (NameCheck_CardName(self->name) == 1) {
        DebugPrintf(messages + 0x1950);
        return 0;
    }
    bitpack_read_field_by_name(pack, messages + 0x12B0, &value, 0);
    self->lastChara = value;
    bitpack_read_field_by_name(pack, messages + 0x12C0, &value, 0);
    self->lastKart = value;
    bitpack_read_field_by_name(pack, lbl_806DA0E8, &title, 0);
    bitpack_read_field_by_name(pack, messages + 0x12D0, &titleParam, 0);
    bitpack_read_field_by_name(pack, messages + 0x1608, &titleParam2, 0);
    u8 param = titleParam | ((titleParam2 & 1) << 3);
    TitleDecode(lbl_806D10A0 == 0 ? 0 : lbl_806D10A0, &self->title19B, &self->title19C, &self->title1B1, (u16)title,
                param);
    bitpack_read_field_by_name(pack, messages + 0x12EC, &value, 0);
    self->lastGetItem = value;
    bitpack_read_field_by_name(pack, messages + 0x12FC, &value, 0);
    self->coinMilage = (u16)value;
    bitpack_read_field_by_name(pack, messages + 0x1688, &value, 0);
    self->rankin = value;
    bitpack_read_field_by_name(pack, lbl_806DA0F0, &value, 0);
    self->volume = value;
    bitpack_read_field_by_name(pack, lbl_806DA0F8, &value, 0);
    self->wins = value;
    bitpack_read_field_by_name(pack, lbl_806DA100, &value, 0);
    self->lose = value;
    bitpack_read_field_by_name(pack, lbl_806DA0D0, &value, 0);
    self->remain = value;
    bitpack_read_field_by_name(pack, lbl_806DA0D8, &value, 0);
    self->update = value != 0;
    bitpack_read_field_by_name(pack, messages + 0x12A4, &value, 0);
    self->cameraTag = value != 0;
    bitpack_read_field_by_name(pack, messages + 0x167C, &value, 0);
    self->liveTag = value != 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            bitpack_read_field_by_name(pack, ((const char *const (*)[8])(messages + 0x18F0))[i][j], &rank, 0);
            self->cupRank[i][j] = rank & 0xF;
        }
    }
    bitpack_read_field_by_name(pack, messages + 0x15C8, &stat14, 0);
    bitpack_read_field_by_name(pack, messages + 0x15D8, &stat18, 0);
    bitpack_read_field_by_name(pack, messages + 0x15E8, &stat19, 0);
    bitpack_read_field_by_name(pack, messages + 0x15F8, &stat1A, 0);
    bitpack_read_field_by_name(pack, messages + 0x1618, &stat1C, 0);
    bitpack_read_field_by_name(pack, messages + 0x1628, &stat20, 0);
    bitpack_read_field_by_name(pack, messages + 0x1638, &stat24, 0);
    self->stat14 = stat14;
    self->stat18 = stat18;
    self->stat19 = stat19 != 0;
    self->stat1A = stat1A != 0;
    self->stat1C = stat1C;
    self->stat20 = stat20;
    self->stat24 = stat24;
    for (unsigned int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            bitpack_read_field_by_name(pack, ((const char *const *)(messages + 0x170C))[i], &flag, j);
            self->flags48[i][j] = flag & 1;
        }
    }
    for (unsigned int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            bitpack_read_field_by_name(pack, ((const char *const *)(messages + 0x172C))[i], &flag, j);
            self->flags88[i][j] = flag & 1;
        }
    }
    getItem = 0;
    for (int i = 0; i < 0x69; i++) {
        bitpack_read_field_by_name(pack, messages + 0x12DC, &getItem, i);
        self->getItem[i] = getItem != 0;
    }
    for (int i = 0; i < 0x78; i++) {
        const ItemUnlockEntry *e = &((const ItemUnlockEntry *)(messages + 0x848))[i];
        if (e->item >= 0 && self->getItem[e->item] == 1 && e->unlock >= 0) {
            self->unlockFlags[e->unlock] = 1;
        }
    }
    itemPack = 0;
    for (int i = 0; i < 3; i++) {
        bitpack_read_field_by_name(pack, messages + 0x130C, &itemPack, i);
        self->itemPack[i] = itemPack;
    }
    bitpack_read_field_by_name(pack, lbl_806DA108, &missGp, 0);
    self->missGp = missGp != 0;
    bitpack_read_field_by_name(pack, messages + 0x15B8, &playCount, 0);
    self->playCount = playCount;
    bitpack_read_field_by_name(pack, messages + 0x1648, &clear, 0);
    self->lastClearClass = clear;
    bitpack_read_field_by_name(pack, messages + 0x1664, &clear, 0);
    self->lastClearUra = clear != 0;
    if (publish == 1) {
        g_characterId = self->lastChara;
        int variant = 2;
        if (self->lastKart == 0) {
            variant = 0;
        }
        SetKartVariant(variant);
        if (AllCupsCleared(self, 0) == 1) {
            lbl_806D12E4[0] = 1;
        }
        if (AllCupsCleared(self, 1) == 1) {
            lbl_806D12E4[1] = 1;
        }
        if (AllCupsCleared(self, 2) == 1) {
            lbl_806D12E4[2] = 1;
        }
    }
    return 1;
}
