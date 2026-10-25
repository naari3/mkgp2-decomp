extern void TexMgr_SetTexture(void *tex, ...);

void fn_801D8DF8(char *self, int tex, int idx) {
    TexMgr_SetTexture(((void **)(self + 0x5C))[idx], tex);
}
