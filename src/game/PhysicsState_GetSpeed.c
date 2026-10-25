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

void fn_801EC7B4(char *self, const float *v) {
    float *p = (float *)(self + 0xD8);
    p[0] = p[0] + v[0];
    p[1] = p[1] + v[1];
    p[2] = p[2] + v[2];
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

void PhysicsState_SetPosition(char *self, float *pos) {
    float *p = (float *)(self + 0x4C);
    p[0] = pos[0];
    p[1] = pos[1];
    p[2] = pos[2];
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
