typedef struct KartMovement KartMovement;

unsigned int KartMovement_CanReceiveItem(KartMovement *km, unsigned char param_2) {
    int state = *(int *)((char *)km + 0x1f0);
    if (state == -1) return 0;
    if (state == -1) return 0;
    if (state == 0x17) return 0;
    if (state == 0x1c) return 0;
    if (*(unsigned char *)((char *)km + 0x2b0) == 1) return 0;
    if ((param_2 != 0) && (*(unsigned char *)((char *)km + 0x2b1) == 1)) return 0;
    return 1;
}

unsigned int GetAnimState(KartMovement *km) {
    return *(unsigned int *)((char *)km + 0x1f0);
}
