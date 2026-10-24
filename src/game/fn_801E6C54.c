void fn_801E6C54(char *self, unsigned char v) {
    *(unsigned char *)(self + 0x94) = v;
}

void KartController_SetTargetSpeed(char *self, float a, float b) {
    *(float *)(self + 0x8C) = b;
    *(float *)(self + 0x90) = a;
}
