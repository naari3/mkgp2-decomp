/* Card save parsing and integrity check: one TU that owns the card parameter
 * tables and field-name pool (.rodata 0x80315378..0x803175A0). */
#include "game/CardSaveParserPrivate.h"
#include "game/CardChecksumPoolPrivate.h"

/* Assembly-grounded card v2 decoder. Unknown destination fields retain byte offsets. */
extern u32 isJapanese(void);
extern void *memset(void *, int, unsigned int);
extern u16 fn_801F8D58(u16);
extern u8 NameCheck_CardName(u16 *);
extern int g_characterId;
extern const char lbl_806D3448[8], lbl_806D3450[7], lbl_806D3458[7];
extern const char lbl_806D3460[5], lbl_806D3468[6], lbl_806D3470[6];
extern const char lbl_806D3478[7], lbl_806D3480[4], lbl_806D3484[5], lbl_806D348C[5];
extern const char lbl_806D3494[8];
extern const char *const lbl_806D349C[2];

static inline void StoreCardRaceResult(u8 *row, u8 *flags,
    const u32 *rank, const u32 *wins, const u32 *cleared,
    const u32 *visited, const u32 *award)
{
    u32 progress = 2;
    *(u32 *)row = *rank;
    flags[0] = *wins;
    flags[4] = *cleared != 0;
    flags[8] = *visited != 0;
    if (*award == 0) progress = 0;
    *(u32 *)(row + 0x1C) = progress;
}

static inline int CardUnlockRuleSlot(const CardUnlockRule *rule)
{
    return rule->slot;
}

u8 CardSaveData_Parser(u8 *dest, void *pack, u8 publish)
{
    u32 locale = 0, name, value;
    u32 cupRank;
    u32 rank, wins, cleared, visited, award;
    u32 grid, extra, unlock, counter, enabled, selection, selectedFlag;
    u32 mileage, total;
    int i;
    unsigned int group;
    const char *const *fields;
    const CardUnlockRule *rule;
    bitpack_read_field_by_name(pack, lbl_806D3448, &locale, 0);
    if (locale != isJapanese()) return 0;
    memset(dest, 0, 12);
    {
        int i;
        u16 *cardName = (u16 *)dest;
        for (i = 0; i < 5; i++) {
            bitpack_read_field_by_name(pack, lbl_806D3460, &name, i);
            cardName[i] = fn_801F8D58((u8)name);
        }
    }
    if (NameCheck_CardName((u16 *)dest) == 1) {
        DebugPrintf((const char *)lbl_80317544);
        return 0;
    }
    bitpack_read_field_by_name(pack, lbl_806D3468, &value, 0); dest[0xC] = value;
    bitpack_read_field_by_name(pack, lbl_806D3470, &value, 0); dest[0x17B] = value;
    bitpack_read_field_by_name(pack, (const char *)lbl_80317124, &value, 0); dest[0x17C] = value;
    bitpack_read_field_by_name(pack, (const char *)lbl_80317434, &value, 0); dest[0x17C] |= (value << 3) & 8;
    bitpack_read_field_by_name(pack, lbl_806D3478, &value, 0); dest[0xD] = value;
    bitpack_read_field_by_name(pack, (const char *)lbl_80317140, &value, 0); dest[0xE] = value;
    bitpack_read_field_by_name(pack, lbl_806D3480, &value, 0); *(u32 *)(dest+0x40) = value;
    bitpack_read_field_by_name(pack, lbl_806D3484, &value, 0); *(u16 *)(dest+0x48) = value;
    bitpack_read_field_by_name(pack, lbl_806D348C, &value, 0); *(u16 *)(dest+0x4A) = value;
    bitpack_read_field_by_name(pack, lbl_806D3450, &value, 0); dest[0x16C] = value;
    bitpack_read_field_by_name(pack, lbl_806D3458, &value, 0); dest[0x16D] = value != 0;
    bitpack_read_field_by_name(pack, (const char *)lbl_8031739C, &value, 0); dest[0x17D] = value != 0;
    {
        u8 *cursor;
        u8 *row;
        const char *const *fields;
        unsigned int group;
        int i, j;
    row = dest;
    fields = lbl_80317454;
    for (group = 0; group < 6; row += 4, group++, fields++) {
        for (i = 0, cursor = row; i < 4; i++, cursor++) {
            bitpack_read_field_by_name(pack, *fields, &cupRank, i);
            cursor[0xF] = cupRank;
        }
    }
    }
    {
        u8 *row;
        int i, j;
        unsigned int group;
        u8 *cursor;
        const char *const *fields;
    for (i = 0, row = dest; i < 4; i++, row += 4) {
        bitpack_read_field_by_name(pack, (const char *)lbl_8031727C, &rank, i);
        bitpack_read_field_by_name(pack, (const char *)lbl_80317288, &wins, i);
        bitpack_read_field_by_name(pack, (const char *)lbl_80317294, &cleared, i);
        bitpack_read_field_by_name(pack, (const char *)lbl_803172A0, &visited, i);
        bitpack_read_field_by_name(pack, (const char *)lbl_803173A8, &award, i);
        StoreCardRaceResult(row + 0x4C, dest + 0x5C + i,
            &rank, &wins, &cleared, &visited, &award);
    }
    }
    bitpack_read_field_by_name(pack, (const char *)lbl_803173F4, &rank, 0);
    bitpack_read_field_by_name(pack, (const char *)lbl_80317404, &wins, 0);
    bitpack_read_field_by_name(pack, (const char *)lbl_80317414, &cleared, 0);
    bitpack_read_field_by_name(pack, (const char *)lbl_80317424, &visited, 0);
    bitpack_read_field_by_name(pack, (const char *)lbl_80317444, &award, 0);
    *(u32 *)(dest+0x78) = rank;
    dest[0x7C] = wins;
    dest[0x7D] = cleared != 0;
    dest[0x7E] = visited != 0;
    {
        u32 progress = 2;
        if (award == 0) progress = 0;
        *(u32 *)(dest+0x80) = progress;
    }
    {
        unsigned int group;
        int i, j;
        u8 *cursor, *row;
        const char *const *fields;
    row = dest;
    fields = lbl_80317484;
    for (group = 0; group < 6; row += 4, group++, fields++) {
        cursor = row;
        for (i = 0; i < 4; i++, cursor++) {
            bitpack_read_field_by_name(pack, *fields, &grid, i);
            cursor[0x9C] = grid != 0;
        }
    }
    }
    {
        unsigned int group;
        int i, j;
        u8 *cursor, *row;
        const char *const *fields;
    row = dest;
    fields = lbl_8031746C;
    for (group = 0; group < 6; row += 4, group++, fields++) {
        extra = 0;
        cursor = row;
        for (i = 0; i < 4; i++, cursor++) {
            bitpack_read_field_by_name(pack, *fields, &extra, i);
            cursor[0x84] = extra != 0;
        }
    }
    }
    unlock = 0;
    for (i = 0; i < 100; i++) {
        bitpack_read_field_by_name(pack, (const char *)lbl_80317130, &unlock, i);
        dest[0xF0+i] = unlock != 0;
    }
    rule = (const CardUnlockRule *)lbl_803160C0;
    for (i = 0; i < 203; i++, rule++) {
        if (rule->savedFlag >= 0 && dest[0xF0+rule->savedFlag] == 1 && rule->category >= 0)
            dest[0xB4+rule->category] = 1;
        if (rule->group >= 0 && rule->savedFlag >= 0 && dest[0xF0+rule->savedFlag] == 1)
            dest[(rule->group*4+CardUnlockRuleSlot(rule))+0x23] = 1;
    }
    {
        const char *const *fields;
        int i;
        unsigned int group;
        u8 *cursor, *row;
        int j;
    row = dest;
    fields = lbl_806D349C;
    for (group = 0; group < 2; row += 12, group++, fields++) {
        counter = 0;
        cursor = row;
        for (j = 0; j < 3; j++, cursor += 4) {
            bitpack_read_field_by_name(pack, *fields, &counter, j);
            *(u32 *)(cursor+0x154) = counter;
        }
    }
    }
    enabled = 0;
    bitpack_read_field_by_name(pack, lbl_806D3494, &enabled, 0);
    dest[0x16E] = enabled != 0;
    fields = lbl_80317514;
    for (group = 0; group < 6; group++, fields += 2) {
        selection = 0; selectedFlag = 0;
        bitpack_read_field_by_name(pack, fields[0], &selection, 0);
        bitpack_read_field_by_name(pack, fields[1], &selectedFlag, 0);
        dest[0x16F+group] = selection;
        dest[0x175+group] = selectedFlag != 0;
    }
    mileage = 0;
    bitpack_read_field_by_name(pack, (const char *)lbl_803173B8, &mileage, 0); *(u32 *)(dest+0x18C) = mileage;
    bitpack_read_field_by_name(pack, (const char *)lbl_803173C8, &mileage, 0); *(u32 *)(dest+0x188) = mileage;
    *(u32 *)(dest+0x190) = *(u32 *)(dest+0x188) + *(u32 *)(dest+0x18C);
    total = 0;
    bitpack_read_field_by_name(pack, (const char *)lbl_803173E0, &total, 0); *(u32 *)(dest+0x194) = total;
    if (publish == 1) g_characterId = (signed char)dest[0xC];
    return 1;
}

/* Assembly-grounded v1 unpack view; unknown player fields stay opaque. */

extern u8 bitpack_read_field_by_name(void *pack, const char *name, u32 *out, int index);
extern u32 isJapanese(void);
extern void *memset(void *dst, int value, unsigned int size);
extern u16 fn_801F8D58(u16 value);
extern u8 NameCheck_CardName(u16 *name);
extern void DebugPrintf(const char *format, ...);
extern int g_characterId;

/* Sizes are the actual symbols.txt string extents, not guessed SDA hints. */
extern const char lbl_806D3448[8];
extern const char lbl_806D3450[7];
extern const char lbl_806D3458[7];
extern const char lbl_806D3460[5];
extern const char lbl_806D3468[6];
extern const char lbl_806D3478[7];
extern const char lbl_806D3484[5];
extern const char lbl_806D348C[5];

u8 card_unpack_v1(u8 *dest, void *pack, u8 publish_character)
{
    u32 locale = 0;
    u32 name_value;
    u32 value;
    u32 flag_value;
    u8 flag0 = 0;
    u8 flag1 = 0;
    u8 flag2 = 0;
    u16 *cursor;
    int i;
    int unlock_index;

    bitpack_read_field_by_name(pack, lbl_806D3448, &locale, 0);
    if (locale != isJapanese()) {
        return 0;
    }
    memset(dest, 0, 12);
    i = 0;
    cursor = (u16 *)dest;
    for (; i < 5; i++, cursor++) {
        bitpack_read_field_by_name(pack, lbl_806D3460, &name_value, i);
        *cursor = fn_801F8D58((u8)name_value);
    }
    if (NameCheck_CardName((u16 *)dest) == 1) {
        DebugPrintf(lbl_80317544);
        return 0;
    }

    bitpack_read_field_by_name(pack, lbl_806D3468, &value, 0);
    dest[0xC] = value;
    dest[0x17B] = 0xFF;
    dest[0x17C] = 0;
    bitpack_read_field_by_name(pack, lbl_806D3478, &value, 0);
    dest[0xD] = value;
    bitpack_read_field_by_name(pack, lbl_806D3484, &value, 0);
    *(u16 *)(dest + 0x48) = value;
    bitpack_read_field_by_name(pack, lbl_806D348C, &value, 0);
    *(u16 *)(dest + 0x4A) = value;
    bitpack_read_field_by_name(pack, lbl_806D3450, &value, 0);
    dest[0x16C] = value;
    bitpack_read_field_by_name(pack, lbl_806D3458, &value, 0);
    dest[0x16D] = value != 0;
    flag_value = 0;
    for (unlock_index = 0; unlock_index < 100; unlock_index++) {
        bitpack_read_field_by_name(pack, lbl_80317130, &flag_value, unlock_index);
        if (flag_value == 1) {
            if (unlock_index == 0) flag0 = 1;
            if (unlock_index == 1) flag1 = 1;
            if (unlock_index == 2) flag2 = 1;
        }
    }
    if (publish_character == 1) {
        g_characterId = (signed char)dest[0xC];
    }
    if (!flag0) flag0 = 1;
    else if (!flag1) flag1 = 1;
    else if (!flag2) flag2 = 1;
    dest[0xF0] = flag0;
    dest[0xF1] = flag1;
    dest[0xF2] = flag2;
    return 1;
}

#pragma use_lmw_stmw off
/* Packed card integrity check; the first argument is unused by this format. */
extern void *bitpack_init(void *, void *, int, void *, u8);
extern void bitpack_write_field(void *, u32, const char *, int);
extern u8 Card_VerifyChecksum_data_803FED40[0x30];
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
    bitpack_init(pack, Card_VerifyChecksum_data_803FED40, 3, raw, 0);
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
    
    for (j = 0; j < 3; j++) {
        bitpack_read_field_by_name(pack, lbl_803170FC, &signature, j);
        DebugPrintf(lbl_806D34A8, signature);
        if (lbl_806D34A4[j] != signature) return -1;
    }
    DebugPrintf(lbl_806D34AC);
    version = -1;
    bitpack_read_field_by_name(pack, lbl_806D3440, &version, 0);
    DebugPrintf(lbl_80317594, version);
    return version;
}
#pragma use_lmw_stmw reset
