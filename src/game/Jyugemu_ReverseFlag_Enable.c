typedef unsigned char u8;

extern u8 lbl_806CEFC0[8];

void Jyugemu_ReverseFlag_SetEnable(u8 enable) {
    lbl_806CEFC0[0] = enable;
}
