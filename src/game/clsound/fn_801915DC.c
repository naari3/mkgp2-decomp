typedef struct Entry {
    unsigned char pad[0x10];
    unsigned char val;
    unsigned char pad2[0xb];
} Entry;
extern Entry lbl_80379554[];

unsigned char fn_801915DC(int i) {
    return lbl_80379554[i].val;
}
