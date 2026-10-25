float PhysicsState_GetSpeed(char *self) { return *(float *)(self + 0x68); }
float PhysicsState_GetAngularVelocity(char *self) { return *(float *)(self + 0x8C); }
void *PhysicsState_GetOrientMatrixPtr(char *self) { return self + 0xE4; }
float fn_801EC74C(char *self) { return *(float *)(self + 0x84); }
float fn_801EC754(char *self) { return *(float *)(self + 0x7C); }
float fn_801EC75C(char *self) { return *(float *)(self + 0x7C); }
float PhysicsState_GetHeading(char *self) { return *(float *)(self + 0x84); }
void *PhysicsState_GetPositionPtr(char *self) { return self + 0x4C; }
int PhysicsState_GetCollisionKartIdx(char *self) { return *(int *)(self + 0x128); }
int fn_801EC77C(char *self) { return *(int *)(self + 0x124); }

int fn_801EC784(char *self) {
    int result = 0;
    if (*(unsigned char *)(self + 0xA5) != 0 || *(int *)(self + 0xC0) > 0) {
        result = 1;
    }
    return result;
}

void PhysicsState_SetFlag188(char *self, unsigned char v) { *(unsigned char *)(self + 0x188) = v; }

/* Register allocation of the three fadds could not be reproduced from C. */
asm void fn_801EC7B4(char *self, const float *v) {
    nofralloc
    lfs f2, 0xd8(r3)
    lfs f0, 0x0(r4)
    lfs f1, 0x4(r4)
    fadds f2, f2, f0
    lfs f0, 0x8(r4)
    stfs f2, 0xd8(r3)
    lfs f2, 0xdc(r3)
    fadds f1, f2, f1
    stfs f1, 0xdc(r3)
    lfs f1, 0xe0(r3)
    fadds f0, f1, f0
    stfs f0, 0xe0(r3)
    blr
}

void fn_801EC7E8(char *self, float v) { *(float *)(self + 0x13C) = v; }

void fn_801EC7F0(char *self, unsigned char flag) {
    if (flag) {
        *(int *)(self + 0xC4) = 2;
    } else {
        *(int *)(self + 0xC4) = 0;
    }
}

void fn_801EC810(char *self, unsigned char v) { *(unsigned char *)(self + 0x9C) = v; }
void PhysicsState_SetCollidedObject(char *self, void *obj) { *(void **)(self + 0x124) = obj; }
void fn_801EC820(char *self, float v) { *(float *)(self + 0x84) = v; }
void fn_801EC828(char *self, float v) { *(float *)(self + 0x7C) = v; }

void fn_801EC830(char *self, float v) {
    *(float *)(self + 0x7C) += v;
    *(float *)(self + 0x84) += v;
}

void PhysicsState_SetPosition(char *self, const float *pos) {
    *(float *)(self + 0x4C) = pos[0];
    *(float *)(self + 0x50) = pos[1];
    *(float *)(self + 0x54) = pos[2];
}

void PhysicsState_SetGrounded(char *self, unsigned char v) { *(unsigned char *)(self + 0xA4) = v; }
void PhysicsState_SetField94(char *self, float v) { *(float *)(self + 0x94) = v; }
void PhysicsState_SetField90(char *self, float v) { *(float *)(self + 0x90) = v; }

void PhysicsState_SetSpeedImmediate(char *self, float a, float b) {
    *(float *)(self + 0x6C) = a;
    *(float *)(self + 0x70) = a;
    *(float *)(self + 0x74) = b;
    *(float *)(self + 0x78) = b;
}
