/* Packed card integrity check; the first argument is unused by this format. */
#include "game/CardSaveParserPrivate.h"
#include "game/CardChecksumPoolPrivate.h"
extern void *bitpack_init(void *, void *, int, void *, u8);
extern void bitpack_write_field(void *, u32, const char *, int);
extern u8 lbl_803FED40[0x30];
extern const signed char lbl_806D34A4[3];
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
    int j;
    int i;
    const signed char *expected;
    bitpack_init(pack, lbl_803FED40, 3, raw, 0);
    checksum = 0;
    sum = 0;
    bitpack_read_field_by_name(pack, lbl_80317108, &checksum, 0);
    bitpack_write_field(pack, 0, lbl_80317108, 0);
    for (i = 0; i < 0x45; i++) sum += *raw++;
    bitpack_write_field(pack, checksum, lbl_80317108, 0);
    sum &= 0xFF;
    DebugPrintf(lbl_80317558, sum, checksum);
    if (sum != checksum) {
        DebugPrintf(lbl_80317574);
        return -1;
    }
    DebugPrintf(lbl_80317588);
    expected = lbl_806D34A4;
    for (j = 0; j < 3; j++, expected++) {
        bitpack_read_field_by_name(pack, lbl_803170FC, &signature, j);
        DebugPrintf(lbl_806D34A8, signature);
        if (*expected != signature) return -1;
    }
    DebugPrintf(lbl_806D34AC);
    version = -1;
    bitpack_read_field_by_name(pack, lbl_806D3440, &version, 0);
    DebugPrintf(lbl_80317594, version);
    return version;
}
