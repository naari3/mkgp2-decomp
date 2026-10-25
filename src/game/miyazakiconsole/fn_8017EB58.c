typedef struct Node {
    char pad[0x38];
    unsigned int idx;
} Node;

extern unsigned int lbl_806CFB74;
extern unsigned char lbl_806CFB78;
extern Node *lbl_806D165C;
extern void *lbl_806D166C;
extern char *lbl_806D1670;
extern const char lbl_80376B88[];
extern void fn_801909A4(int);
extern void fn_801908F0(void);
extern void ClSound_PlayBgmStream(int slot, int id);
extern void clStream_setVolume(int slot, int vol);
extern void fn_801814C8(void);
extern void fn_8017FF10(void *, char *, const char *, ...);

int fn_8017EB58(int msg, int a1, int arg, int a3, int sub) {
    int ofs;
    Node *node;
    void *dst;
    char *buf;
    switch (msg) {
    case 0:
        switch (sub) {
        case 9:
            if (lbl_806CFB74 != 0xFFFFFFFF) {
                fn_801909A4(lbl_806CFB74);
                lbl_806CFB74 = -1;
            }
            ClSound_PlayBgmStream(arg, 0);
            clStream_setVolume(arg, lbl_806CFB78);
            lbl_806CFB74 = arg;
            break;
        case 10:
            break;
        case 11:
            fn_801814C8();
            break;
        }
        return 0;
    case 1:
        return 0;
    case 3:
        return 0;
    case 4:
        node = lbl_806D165C;
        dst = lbl_806D166C;
        buf = lbl_806D1670;
        if (node == 0) {
            ofs = 0;
        } else if (node->idx < 9) {
            ofs = node->idx + 3;
        } else {
            ofs = 12;
        }
        fn_8017FF10(dst, buf + ofs, lbl_80376B88, ofs);
        return 0;
    case 2:
        fn_801908F0();
        lbl_806CFB74 = -1;
        return 0;
    }
    return 0;
}
