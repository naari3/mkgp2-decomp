/*
 * Complete assembly-grounded legacy dispatch draft (NonMatching).
 * Real new expressions retain both constructor-failure delete actions.
 * The remaining source-object difference is version/used register coloring
 * and one extra move after the second used-bits call, not manual EH.
 */
typedef unsigned char u8;
extern "C" {
void DebugPrintf(const char *, ...);
void *memcpy(void *, const void *, unsigned long);
int Card_VerifyChecksum(void *, void *);
void *bitpack_init(void *, void *, int, void *, u8);
int bitpack_get_used_bytes(void *);
int bitpack_get_used_bits(void *);
u8 card_unpack_v1(u8 *, void *, u8);
u8 CardSaveData_Parser(u8 *, void *, u8);
void MemoryManager_TimedFree(void *);
void SetCardVolumeFlagByte(u8);
extern const char lbl_80315378[0x3FC];
extern u8 lbl_803FED70[0x370];
extern u8 lbl_803FF0E0[0x400];
extern u8 g_playerData[0x1DC];
extern u8 lbl_806D12AF;
}
void *operator new(unsigned long);
void operator delete(void *);

class CardBitpack {
    u8 opaque[0x18];
public:
    inline CardBitpack(void *table, int count, void *raw, u8 options) {
        bitpack_init(this, table, count, raw, options);
    }
};

extern "C" u8 card_unpack_legacy_dispatch(u8 *dest, const void *raw, u8 publish)
{
    const char *messages = lbl_80315378;
    u8 result;
    int version;
    int used;
    CardBitpack *pack;
    u8 copy[0x45];

    DebugPrintf(messages + 0x2228);
    if (raw == 0) {
        DebugPrintf(messages + 0x224C);
        return 0;
    }
    result = 0;
    memcpy(copy, raw, 0x45);
    version = Card_VerifyChecksum(dest, copy);
    if (version < 0) return 0;
    memcpy(copy, raw, 0x45);
    if (version >= 0) {
      if (version == 0) {
        pack = new CardBitpack(lbl_803FED70, 0x37, copy, 0);
        if (bitpack_get_used_bytes(pack) <= 0x45)
            result = card_unpack_v1(dest, pack, publish);
        dest[0x16C] = 0;
        if (publish == 1) g_playerData[0x1A0] = 1;
      } else if (version == 1) {
        pack = new CardBitpack(lbl_803FF0E0, 0x40, copy, 0);
        if (bitpack_get_used_bytes(pack) <= 0x45)
            result = CardSaveData_Parser(dest, pack, publish);
      } else {
        DebugPrintf(messages + 0x225C);
        return 0;
      }
    } else {
        DebugPrintf(messages + 0x225C);
        return 0;
    }
    version = 0x228 - bitpack_get_used_bits(pack);
    used = bitpack_get_used_bits(pack);
    DebugPrintf(messages + 0x226C, bitpack_get_used_bytes(pack), used, version);
    /* The original overflow path returns before releasing pack. */
    if (bitpack_get_used_bytes(pack) > 0x45) return 0;
    MemoryManager_TimedFree(pack);
    if (publish == 1 && result == 1) {
        dest[0x17E] = 1;
        lbl_806D12AF = *(int *)(dest + 0x40) >= 1;
        SetCardVolumeFlagByte(dest[0x17E]);
    }
    return result;
}
