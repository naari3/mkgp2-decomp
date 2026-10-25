void fn_801D8A98(char *self, int v) {
    *(int *)(self + 0x8) = v;
}

void fn_801D8AA0(char *self, int v) {
    *(int *)(self + 0x8) = v;
    *(int *)(*(char **)(self + 0x4) + 0x4) = *(int *)(self + 0x8);
}
