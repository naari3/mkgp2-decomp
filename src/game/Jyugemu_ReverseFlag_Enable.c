typedef unsigned char u8;

extern u8 Jyugemu_ReverseFlag_data_806CEFC0[8];

void Jyugemu_ReverseFlag_SetEnable(u8 enable) {
    Jyugemu_ReverseFlag_data_806CEFC0[0] = enable;
}
