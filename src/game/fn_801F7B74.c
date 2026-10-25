extern void fn_801F7604(void *owner, void *self);

void fn_801F7B74(void *owner, char *self, float value) {
    *(float *)(self + 0x10) = value;
    fn_801F7604(owner, self);
}
