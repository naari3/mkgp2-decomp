/*
 * 0x8020F290..0x8020F44C: card session steps (read/write kick, print and
 * eject) and the service trigger checks.
 */

struct PlayerData {
    char pad000[0x1D9];
    signed char cardState;
};

extern "C" {
extern unsigned char lbl_806D1A38;
extern unsigned char lbl_806D1A39;
extern unsigned char lbl_806D1A3A;
extern unsigned char lbl_806D1A3B;
extern unsigned char lbl_806D1A3C;
extern unsigned char lbl_806D1A3D;
extern unsigned char lbl_806D1A3E;
extern int lbl_806D1A40;
extern int lbl_806D1A44;
extern PlayerData g_playerData;
unsigned char card_rw_kick_state_machine(void);
unsigned char card_rw_state_machine_short(void);
unsigned char Sci2Card_EjectAndFinalize_Step(void);
int Sci2Card_GetPrintErrorCode(void);
int Sci2Card_GetUnpackStatusCode(void);
unsigned char Sci2Card_GetByteFlag1224(void);
void card_eject_init(void);
void CardSession_OnServiceTriggerAbort(void);

void fn_8020F290(void) {
    if (lbl_806D1A39 && lbl_806D1A3E != 1) {
        if (!lbl_806D1A3A) {
            if (card_rw_kick_state_machine()) {
                lbl_806D1A3A = 1;
            }
        } else if (!lbl_806D1A3B) {
            if (card_rw_state_machine_short() == 1) {
                lbl_806D1A40 = Sci2Card_GetPrintErrorCode();
                lbl_806D1A3B = 1;
            }
        } else if (lbl_806D1A3D == 1) {
            if (!lbl_806D1A3C) {
                lbl_806D1A3C = 1;
                card_eject_init();
            }
            if (Sci2Card_EjectAndFinalize_Step() == 1) {
                lbl_806D1A44 = Sci2Card_GetPrintErrorCode();
                lbl_806D1A3E = 1;
            }
        }
    }
}

void fn_8020F35C(void) {
    if (Sci2Card_GetByteFlag1224()) {
        lbl_806D1A3D = 1;
    }
}

void fn_8020F38C(unsigned char force) {
    if (Sci2Card_GetByteFlag1224()) {
        if (force || (Sci2Card_GetUnpackStatusCode() != 5 && g_playerData.cardState == 2)) {
            lbl_806D1A39 = 1;
        }
    }
}

int fn_8020F3F0(void) {
    if (lbl_806D1A38 == 1) {
        return 0;
    }
    if (g_playerData.cardState != 2) {
        return 1;
    }
    lbl_806D1A38 = 1;
    CardSession_OnServiceTriggerAbort();
    return 1;
}
}
