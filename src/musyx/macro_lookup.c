typedef unsigned short u16;
typedef unsigned int u32;
typedef struct { u32 a; u16 id; u16 pad; } Key;
extern u16 lbl_806BB598[];
extern unsigned char lbl_806BBD98[];
extern void* lbl_806D1F7C;
extern Key lbl_806D1F80;
extern u32 lbl_806D1F88;
extern u32 lbl_806D1F8C;
extern void* fn_802B9450(void* key, void* base, u32 n, u32 size, int (*cmp)(const void*, const void*));

int fn_802A8E3C(const void* a, const void* b) {
    return ((Key*)a)->id - ((Key*)b)->id;
}

u32 fn_802A8E4C(u16 id) {
    u32 n;
    lbl_806D1F88 = (id >> 6) & 0x3FF;
    n = lbl_806BB598[lbl_806D1F88 * 2];
    if (n != 0) {
        lbl_806D1F80.id = id;
        lbl_806D1F8C = lbl_806BB598[lbl_806D1F88 * 2 + 1];
        lbl_806D1F7C = fn_802B9450(&lbl_806D1F80, lbl_806BBD98 + lbl_806D1F8C * 8, n, 8, fn_802A8E3C);
        if (lbl_806D1F7C != 0) {
            return *(u32*)lbl_806D1F7C;
        }
    }
    return 0;
}
