typedef struct RelocNode {
    unsigned char flag;
    char pad[7];
    struct RelocNode *child;
    char pad2[0x54 - 0xc];
} RelocNode;
void fn_801A0BE0(char *base, RelocNode *n) {
    int i;
    if (n == 0) return;
    for (i = 0;; i++) {
        if (n[i].child != 0 && (unsigned int)n[i].child < 0x80000000) {
            n[i].child = (RelocNode *)(base + (unsigned int)n[i].child);
            fn_801A0BE0(base, n[i].child);
        }
        if (n[i].flag & 1) break;
    }
}
