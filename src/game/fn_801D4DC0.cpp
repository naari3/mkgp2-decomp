typedef unsigned char u8;
extern "C" {
void *bitpack_init(void *, void *, int, void *, u8);
void bitpack_read_field_by_name(void *, const char *, unsigned int *, int);
void bitpack_write_field(void *, unsigned int, const char *, int);
void DebugPrintf(const char *, ...);
extern const char lbl_8039C718[];
extern u8 lbl_8049B670[];
extern signed char lbl_806DA110[4];
extern char lbl_806DA114[4], lbl_806DA118[4], lbl_806DA0C0[8];
}
extern "C" int fn_801D4DC0(void *self, u8 *raw) {
    const char *messages = lbl_8039C718;
    u8 pack[0x18];
    unsigned int checksum;
    unsigned int value;
    int version;
    unsigned int sum;
    int i;
    bitpack_init(pack, lbl_8049B670, 3, raw, 0);
    checksum = 0;
    sum = 0;
    bitpack_read_field_by_name(pack, messages + 0x1298, &checksum, 0);
    bitpack_write_field(pack, 0, messages + 0x1298, 0);
    for (i = 0; i < 0x45; i++) sum += *raw++;
    bitpack_write_field(pack, checksum, messages + 0x1298, 0);
    sum &= 255;
    DebugPrintf(messages + 0x1964, sum, checksum);
    if (sum != checksum) {
        DebugPrintf(messages + 0x1980);
        return -1;
    }
    DebugPrintf(messages + 0x1994);
    for (i = 0; i < 3; i++) {
        bitpack_read_field_by_name(pack, messages + 0x128C, &value, i);
        DebugPrintf(lbl_806DA114, value);
        if ((unsigned int)lbl_806DA110[i] != value) return -1;
    }
    DebugPrintf(lbl_806DA118);
    version = -1;
    bitpack_read_field_by_name(pack, lbl_806DA0C0, (unsigned int *)&version, 0);
    DebugPrintf(messages + 0x19A0, version);
    return version;
}
