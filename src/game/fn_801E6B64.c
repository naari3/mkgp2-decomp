extern void PhysicsState_SetPosition(void *phys, const float *pos);

void fn_801E6B64(char *self, const float *pos) {
    void *phys;
    *(float *)(self + 0x30) = pos[0];
    *(float *)(self + 0x34) = pos[1];
    *(float *)(self + 0x38) = pos[2];
    phys = *(void **)(self + 0x20);
    if (phys != 0) {
        PhysicsState_SetPosition(phys, pos);
    }
}
