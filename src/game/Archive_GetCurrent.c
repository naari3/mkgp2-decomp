void *Archive_GetCurrent(void *self) {
    return *(void **)((char *)self + 0x10);
}
