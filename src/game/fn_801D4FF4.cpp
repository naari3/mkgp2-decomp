#include "game/types/size_t.h"
#include "game/PlayerCardBitpackPendingPrivate.h"
extern "C" {
void DebugPrintf(const char *, ...);
void *memcpy(void *, const void *, unsigned long);
int fn_801D4DC0(void *, u8 *);
void *bitpack_init(void *, void *, int, void *, u8);
int bitpack_get_used_bytes(void *);
int bitpack_get_used_bits(void *);
u8 card_unpack(u8 *, void *, u8);
void CardData_InitDefaults(void *, int);
u8 card_unpack_legacy_dispatch(void *, const void *, u8);
u8 fn_801D4118(void *, void *);
void MemoryManager_TimedFree(void *);
void SetCardVolumeFlagByte(u8);
extern char lbl_8039C718[];
extern u8 lbl_8049B6A0[];
extern u8 lbl_806D12AF;
}
void *operator new(size_t);
void operator delete(void *);
extern "C" u8 fn_801D4FF4(u8 *self, const void *raw, u8 publish) {
    const char *messages = lbl_8039C718;
    u8 result;
    int version;
    PlayerCardBitpack *pack;
    u8 copy[0x45];
    u8 legacy[0x1A0];
    DebugPrintf(messages + 0x19AC);
    if (!raw) { DebugPrintf(messages + 0x19D0); return 0; }
    result = 0;
    memcpy(copy, raw, 0x45);
    version = fn_801D4DC0(self, copy);
    if (version < 0) return 0;
    self[0x1D9] = version;
    pack = 0;
    memcpy(copy, raw, 0x45);
    if (((signed char *)self)[0x1D9] >= 0) {
        if (((signed char *)self)[0x1D9] == 2) {
            pack = new PlayerCardBitpack(lbl_8049B6A0, 0x49, copy, 0);
            if (bitpack_get_used_bytes(pack) <= 0x45) result = card_unpack(self, pack, publish);
        } else if (((signed char *)self)[0x1D9] == 1 || ((signed char *)self)[0x1D9] == 0) {
            CardData_InitDefaults(legacy, 1);
            result = card_unpack_legacy_dispatch(legacy, raw, 0);
            if (result == 0) DebugPrintf(messages + 0x19E0);
            if (result == 1) result = fn_801D4118(self, legacy);
            if (result == 0) DebugPrintf(messages + 0x19FC);
            DebugPrintf(messages + 0x1A14);
        } else { DebugPrintf(messages + 0x1A20); return 0; }
    } else { DebugPrintf(messages + 0x1A20); return 0; }
    if (pack) {
        DebugPrintf(messages + 0x1A30, bitpack_get_used_bytes(pack),
                    bitpack_get_used_bits(pack), 0x228 - bitpack_get_used_bits(pack));
        if (bitpack_get_used_bytes(pack) > 0x45) return 0;
        MemoryManager_TimedFree(pack);
    }
    if (publish == 1 && result == 1) {
        self[0x19F] = 1;
        lbl_806D12AF = 1;
        SetCardVolumeFlagByte(self[0x19F]);
    }
    return result;
}
