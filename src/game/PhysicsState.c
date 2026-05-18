/*
 * PhysicsState byte-field setters.
 *
 * dtk reversed-extab group auto_03_801EC99C_text (eg_sz=2):
 *   PhysicsState_SetBrake @ 0x801EC99C: stb r4, 0x88(r3); blr
 *   PhysicsState_SetAccel @ 0x801EC9A4: stb r4, 0x64(r3); blr
 */

void PhysicsState_SetBrake(void *self, unsigned char value) {
    *((unsigned char *)self + 0x88) = value;
}

void PhysicsState_SetAccel(void *self, unsigned char value) {
    *((unsigned char *)self + 0x64) = value;
}
