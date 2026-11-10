/* Packed card integrity check; the first argument is unused by this format. */
#include "game/CardSaveParserPrivate.h"
extern void *bitpack_init(void *, void *, int, void *, u8);
extern void bitpack_write_field(void *, u32, const char *, int);
extern u8 Card_VerifyChecksum_data_803FED40[0x30];
extern const signed char lbl_806D34A4[1];
extern const char lbl_806D34A8[3];
extern const char lbl_806D34AC[2];
extern const char lbl_806D3440[8];

int Card_VerifyChecksum(void *unused, u8 *raw)
{
    u8 pack[0x18];
    u32 checksum;
    u32 signature;
    u32 version;
    u32 sum;
    int i;
    const signed char *expected;
    const char *messages = (const char *)CardSaveData_Parser_rodata_80315378;
    bitpack_init(pack, Card_VerifyChecksum_data_803FED40, 3, raw, 0);
    checksum = 0;
    sum = 0;
    bitpack_read_field_by_name(pack, messages + 0x1D90, &checksum, 0);
    bitpack_write_field(pack, 0, messages + 0x1D90, 0);
    { u8 *p = raw; for (i = 0; i < 0x45; i++) sum += *p++; }
    bitpack_write_field(pack, checksum, messages + 0x1D90, 0);
    sum &= 0xFF;
    DebugPrintf(messages + 0x21E0, sum, checksum);
    if (sum != checksum) {
        DebugPrintf(messages + 0x21FC);
        return -1;
    }
    DebugPrintf(messages + 0x2210);
    expected = lbl_806D34A4;
    for (i = 0; i < 3; i++, expected++) {
        bitpack_read_field_by_name(pack, messages + 0x1D84, &signature, i);
        DebugPrintf(lbl_806D34A8, signature);
        if (*expected != signature) return -1;
    }
    DebugPrintf(lbl_806D34AC);
    version = -1;
    bitpack_read_field_by_name(pack, lbl_806D3440, &version, 0);
    DebugPrintf(messages + 0x221C, version);
    return version;
}
