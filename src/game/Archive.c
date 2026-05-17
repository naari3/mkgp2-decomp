void *Archive_GetRootJObj(void *archive) {
    void *root = *(void **)((char *)archive + 0x2c);
    if (root != 0) return root;
    return 0;
}
