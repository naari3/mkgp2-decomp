extern unsigned char fn_8016C360(int id);
extern void fn_8016C394(int id);

void fn_8018DFC4(void *self, unsigned char flag) {
    if (!flag && fn_8016C360(0x38)) {
        fn_8016C394(0x38);
    }
}
