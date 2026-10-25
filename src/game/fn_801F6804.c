typedef signed char s8;
typedef int s32;
typedef s32 M2C_UNK;

M2C_UNK fn_80266DEC(void *);
M2C_UNK fn_8026A2BC(void *);
M2C_UNK fn_8026A5BC(void *);
M2C_UNK fn_8026A658(void *, void *, void *, void *);

void fn_801F6804(s8 *arg0) {
    *arg0 = 1;
    fn_80266DEC(arg0 + 4);
    fn_8026A2BC(arg0 + 8);
    fn_8026A5BC(arg0 + 0x24);
    fn_8026A658(arg0 + 0x3C, arg0 + 0x40, arg0 + 0x44, arg0 + 0x48);
}
