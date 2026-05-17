typedef struct InputObj {
    unsigned char pad0[0x8];
    unsigned int pressedMask;
    unsigned int heldMask;
    unsigned char pad10[0xc];
    float steering;
    float accelerator;
    float brake;
} InputObj;

unsigned int InputObj_GetHeldMasked(InputObj *self, unsigned int mask) {
    return self->heldMask & mask;
}

unsigned int InputObj_GetPressedMasked(InputObj *self, unsigned int mask) {
    return self->pressedMask & mask;
}

int InputObj_IsHeld(InputObj *self, unsigned int mask) {
    return (mask & self->heldMask) != 0;
}

int InputObj_IsPressed(InputObj *self, unsigned int mask) {
    return (mask & self->pressedMask) != 0;
}

float InputObj_GetBrake(InputObj *self) {
    return self->brake;
}

float InputObj_GetAccelerator(InputObj *self) {
    return self->accelerator;
}

float InputObj_GetSteering(InputObj *self) {
    return self->steering;
}
