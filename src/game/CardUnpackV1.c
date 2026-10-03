/* Assembly-grounded v1 unpack view; unknown player fields stay opaque. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

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
extern const char lbl_80317130[0xE];
extern const char lbl_80317544[0x13C];

u8 card_unpack_v1(u8 *dest, void *pack, u8 publish_character)
{
    u32 locale = 0;
    u32 name_value;
    u32 value;
    u32 flag_value;
    u8 flag0 = 0;
    u8 flag1 = 0;
    u8 flag2 = 0;
    int i;
    u16 *cursor;

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
    for (i = 0; i < 100; i++) {
        bitpack_read_field_by_name(pack, lbl_80317130, &flag_value, i);
        if (flag_value == 1) {
            if (i == 0) flag0 = 1;
            if (i == 1) flag1 = 1;
            if (i == 2) flag2 = 1;
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
