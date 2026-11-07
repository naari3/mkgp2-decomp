/* Assembly-grounded card v2 decoder. Unknown destination fields retain byte offsets. */
#include "game/CardSaveParserPrivate.h"
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
    const char *pool = lbl_80315378;
    bitpack_read_field_by_name(pack, lbl_806D3448, &locale, 0);
    if (locale != isJapanese()) return 0;
    memset(dest, 0, 12);
    {
        int i = 0;
        u16 *nameCursor = (u16 *)dest;
        for (; i < 5; i++, nameCursor++) {
            bitpack_read_field_by_name(pack, lbl_806D3460, &name, i);
            *nameCursor = fn_801F8D58((u8)name);
        }
    }
    if (NameCheck_CardName((u16 *)dest) == 1) {
        DebugPrintf(pool + 0x21CC);
        return 0;
    }
    bitpack_read_field_by_name(pack, lbl_806D3468, &value, 0); dest[0xC] = value;
    bitpack_read_field_by_name(pack, lbl_806D3470, &value, 0); dest[0x17B] = value;
    bitpack_read_field_by_name(pack, pool + 0x1DAC, &value, 0); dest[0x17C] = value;
    bitpack_read_field_by_name(pack, pool + 0x20BC, &value, 0); dest[0x17C] |= (value & 1) << 3;
    bitpack_read_field_by_name(pack, lbl_806D3478, &value, 0); dest[0xD] = value;
    bitpack_read_field_by_name(pack, pool + 0x1DC8, &value, 0); dest[0xE] = value;
    bitpack_read_field_by_name(pack, lbl_806D3480, &value, 0); *(u32 *)(dest+0x40) = value;
    bitpack_read_field_by_name(pack, lbl_806D3484, &value, 0); *(u16 *)(dest+0x48) = value;
    bitpack_read_field_by_name(pack, lbl_806D348C, &value, 0); *(u16 *)(dest+0x4A) = value;
    bitpack_read_field_by_name(pack, lbl_806D3450, &value, 0); dest[0x16C] = value;
    bitpack_read_field_by_name(pack, lbl_806D3458, &value, 0); dest[0x16D] = value != 0;
    bitpack_read_field_by_name(pack, pool + 0x2024, &value, 0); dest[0x17D] = value != 0;
    {
        u8 *cursor;
        u8 *row;
        const char *const *fields;
        unsigned int group;
        int i, j;
    row = dest;
    fields = (const char *const *)(pool + 0x20DC);
    for (group = 0; group < 6; group++, fields++, row += 4) {
        cursor = row;
        for (i = 0; i < 4; i++, cursor++) {
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
    row = dest;
    for (i = 0; i < 4; i++, row += 4) {
        bitpack_read_field_by_name(pack, pool + 0x1F04, &rank, i);
        bitpack_read_field_by_name(pack, pool + 0x1F10, &wins, i);
        bitpack_read_field_by_name(pack, pool + 0x1F1C, &cleared, i);
        bitpack_read_field_by_name(pack, pool + 0x1F28, &visited, i);
        bitpack_read_field_by_name(pack, pool + 0x2030, &award, i);
        *(u32 *)(row+0x4C) = rank;
        dest[0x5C+i] = wins;
        dest[0x60+i] = cleared != 0;
        dest[0x64+i] = visited != 0;
        {
            u32 progress = 2;
            if (award == 0) progress = 0;
            *(u32 *)(row+0x68) = progress;
        }
    }
    }
    bitpack_read_field_by_name(pack, pool + 0x207C, &rank, 0);
    bitpack_read_field_by_name(pack, pool + 0x208C, &wins, 0);
    bitpack_read_field_by_name(pack, pool + 0x209C, &cleared, 0);
    bitpack_read_field_by_name(pack, pool + 0x20AC, &visited, 0);
    bitpack_read_field_by_name(pack, pool + 0x20CC, &award, 0);
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
    fields = (const char *const *)(pool + 0x210C);
    for (group = 0; group < 6; group++, fields++, row += 4) {
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
    fields = (const char *const *)(pool + 0x20F4);
    for (group = 0; group < 6; group++, fields++, row += 4) {
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
        bitpack_read_field_by_name(pack, pool + 0x1DB8, &unlock, i);
        dest[0xF0+i] = unlock != 0;
    }
    rule = (const CardUnlockRule *)(pool + 0xD48);
    for (i = 0; i < 203; i++, rule++) {
        if (rule->savedFlag >= 0 && dest[0xF0+rule->savedFlag] == 1 && rule->category >= 0)
            dest[0xB4+rule->category] = 1;
        if (rule->group >= 0 && rule->savedFlag >= 0 && dest[0xF0+rule->savedFlag] == 1)
            dest[(rule->group*4+rule->slot)+0x23] = 1;
    }
    {
        const char *const *fields;
        int i;
        unsigned int group;
        u8 *cursor, *row;
        int j;
    row = dest;
    fields = lbl_806D349C;
    for (group = 0; group < 2; group++, fields++, row += 12) {
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
    fields = (const char *const *)(pool + 0x219C);
    for (group = 0; group < 6; group++, fields += 2) {
        selection = 0; selectedFlag = 0;
        bitpack_read_field_by_name(pack, fields[0], &selection, 0);
        bitpack_read_field_by_name(pack, fields[1], &selectedFlag, 0);
        dest[0x16F+group] = selection;
        dest[0x175+group] = selectedFlag != 0;
    }
    mileage = 0;
    bitpack_read_field_by_name(pack, pool + 0x2040, &mileage, 0); *(u32 *)(dest+0x18C) = mileage;
    bitpack_read_field_by_name(pack, pool + 0x2050, &mileage, 0); *(u32 *)(dest+0x188) = mileage;
    *(u32 *)(dest+0x190) = *(u32 *)(dest+0x188) + *(u32 *)(dest+0x18C);
    total = 0;
    bitpack_read_field_by_name(pack, pool + 0x2068, &total, 0); *(u32 *)(dest+0x194) = total;
    if (publish == 1) g_characterId = (signed char)dest[0xC];
    return 1;
}
