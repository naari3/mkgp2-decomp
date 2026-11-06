/* Card-name filtering operates on five Shift-JIS code units. */
extern unsigned int wcslen(const unsigned short *);
extern unsigned short *wcscpy(unsigned short *, const unsigned short *);
extern void DebugPrintf(const char *, ...);
extern unsigned char NameCheck_ScanBannedWords(unsigned short *);
extern const char lbl_80318270[];

static inline const unsigned short *NameCheck_ConversionTable(const char *base, int offset)
{
    return (const unsigned short *)(base + offset);
}

unsigned char NameCheck_CardName(const unsigned short *name)
{
    const char *base = lbl_80318270 + 0x10000;
    unsigned short buf[6];
    const unsigned short *converted;
    unsigned short *cursor;
    int leading;
    int i;
    int j;
    if (wcslen(name) > 5) {
        DebugPrintf(base - 0x79a8, wcslen(name));
        return 0;
    }
    wcscpy(buf, name);
    buf[5] = 0;
    cursor = buf;
    for (leading = 0; leading < 5; leading++) {
        if (buf[leading] != 0x8140) break;
    }
    if (leading > 0) {
        for (i = leading; i < 6; i++) buf[i - leading] = buf[i];
    }
    for (i = 4; i >= 0; i--) {
        if (buf[i] != 0x8140 && buf[i] != 0) break;
        buf[i] = 0;
    }
    if (NameCheck_ScanBannedWords(buf) == 1) return 1;
    converted = NameCheck_ConversionTable(base, -0x7b48);
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 81; j++) {
            if (cursor[i] == ((const unsigned short *)(base - 0x7bec))[j]) {
                cursor[i] = converted[j];
                break;
            }
        }
    }
    if (NameCheck_ScanBannedWords(buf) == 1) return 1;
    converted = NameCheck_ConversionTable(base, -0x7c20);
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 26; j++) {
            if (*cursor == ((const unsigned short *)(base - 0x7c54))[j]) {
                *cursor = converted[j];
                break;
            }
        }
        cursor++;
    }
    return NameCheck_ScanBannedWords(buf) == 1;
}
