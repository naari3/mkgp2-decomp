typedef unsigned char u8;

typedef struct StrPcbPartial {
    u8 pad00[0x14];
    int counter14;
    u8 dirty18;
    u8 pad19[0x0D];
    u8 commError26;
    u8 pad27[6];
    u8 command2D;
    u8 command2E;
    u8 command2F;
    u8 status30;
    u8 pad31[3];
    int value34;
    int value38;
    u8 status3C;
    u8 pad3D[3];
    int value40;
    u8 pad44[4];
    float value48;
    float value4C;
    u8 pad50[8];
    u8 errorCode[3];
    u8 pad5B;
    u8 stickyError5C;
} StrPcbPartial;

extern float lbl_806D2400;
extern float lbl_806D2410;
extern float lbl_806D23E0;
extern float lbl_806D23DC;
extern char lbl_806D2414;
extern char lbl_806D2418;

int StrPcb_HasError(StrPcbPartial *self) {
    if ((char)self->errorCode[0] == 'E') {
        if ((char)self->errorCode[1] != '0' || (char)self->errorCode[2] != '0') {
            return 1;
        }
    }
    return self->stickyError5C;
}

u8 StrPcb_GetCommErrorFlag(StrPcbPartial *self) {
    return self->commError26;
}

char *StrPcb_GetErrorCodeString(StrPcbPartial *self) {
    char *code = (char *)self->errorCode;
    if (self->stickyError5C == 0) {
        return &lbl_806D2414;
    }
    if (code[0] == 'E') {
        return code;
    }
    return &lbl_806D2418;
}

#define CLEAR_TRANSIENT(self, zero) do { \
    (self)->status30 = (zero); \
    (self)->value34 = (zero); \
    (self)->value38 = (zero); \
    (self)->status3C = (zero); \
    (self)->value40 = (zero); \
} while (0)

void StrPcb_ResetCommands_Zero(StrPcbPartial *self, u8 resetValues) {
    self->dirty18 = 1; self->command2D = 0;
    self->dirty18 = 1; self->command2E = 0;
    self->dirty18 = 1; self->command2F = 0;
    self->dirty18 = 1; self->counter14 = 0;
    CLEAR_TRANSIENT(self, 0);
    if (resetValues == 1) {
        asm {
            lfs f1, lbl_806D2400(r2)
            lfs f0, lbl_806D2410(r2)
            stfs f1, 0x48(r3)
            stfs f0, 0x4C(r3)
        }
    }
    CLEAR_TRANSIENT(self, 0);
}

void StrPcb_ResetCommands_Neutral(StrPcbPartial *self, u8 resetValues) {
    self->dirty18 = 1; self->command2D = 0x2D;
    self->dirty18 = 1; self->command2E = 0x14;
    self->dirty18 = 1; self->command2F = 0;
    self->dirty18 = 1; self->counter14 = 0;
    CLEAR_TRANSIENT(self, 0);
    if (resetValues == 1) {
        asm {
            lfs f1, lbl_806D23E0(r2)
            lfs f0, lbl_806D23DC(r2)
            stfs f1, 0x48(r3)
            stfs f0, 0x4C(r3)
        }
    }
    CLEAR_TRANSIENT(self, 0);
}
