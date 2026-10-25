typedef signed char s8;
typedef int s32;
typedef s32 M2C_UNK;

M2C_UNK GXGetCullMode(void *);
M2C_UNK GXGetProjectionv(void *);
M2C_UNK GXGetViewportv(void *);
M2C_UNK GXGetScissor(void *, void *, void *, void *);

void fn_801F6804(s8 *arg0) {
    *arg0 = 1;
    GXGetCullMode(arg0 + 4);
    GXGetProjectionv(arg0 + 8);
    GXGetViewportv(arg0 + 0x24);
    GXGetScissor(arg0 + 0x3C, arg0 + 0x40, arg0 + 0x44, arg0 + 0x48);
}
