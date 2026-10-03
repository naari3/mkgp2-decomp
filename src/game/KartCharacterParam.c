/* Only the observed character word is modeled, not a complete Kart layout. */
typedef struct KartCharacterView {
    unsigned char pad00[0x1F8];
    unsigned int characterId;
} KartCharacterView;

extern const float lbl_806D5AB8;
extern const float lbl_806D5ABC;
extern const float lbl_806D5AC0;
extern const float lbl_806D5AC8;
extern const float lbl_806D5ACC;
extern const float lbl_806D5AEC;
extern const float lbl_806D5AF8;
extern const float lbl_806D5B1C;
extern const float lbl_806D5B20;
extern const float lbl_806D5B4C;
extern const float lbl_806D5B50;
extern const float lbl_806D5B54;
extern const float lbl_806D5B58;

float KartCharacterParam_GetBoostFxSizeFactor(const KartCharacterView* self)
{
    switch (self->characterId) {
    case 0: return lbl_806D5AB8;
    case 1: return lbl_806D5AB8;
    case 2: return lbl_806D5ABC;
    case 3: return lbl_806D5AB8;
    case 4: return lbl_806D5AC0;
    case 5: return lbl_806D5AB8;
    case 6: return lbl_806D5AC0;
    case 7: return lbl_806D5AB8;
    case 8: return lbl_806D5AB8;
    case 9: return lbl_806D5AB8;
    case 10: return lbl_806D5AB8;
    case 11: return lbl_806D5AB8;
    case 12: return lbl_806D5AB8;
    default: return lbl_806D5AB8;
    }
}

float KartFxParam_GetConst1p5(void)
{
    return lbl_806D5B4C;
}

float KartCharacterParam_GetFxSizeFactor(const KartCharacterView* self)
{
    switch (self->characterId) {
    case 0: return lbl_806D5AB8;
    case 1: return lbl_806D5B50;
    case 2: return lbl_806D5ABC;
    case 3: return lbl_806D5AB8;
    case 4: return lbl_806D5B54;
    case 5: return lbl_806D5B58;
    case 6: return lbl_806D5B54;
    case 7: return lbl_806D5B50;
    case 8: return lbl_806D5AF8;
    case 9: return lbl_806D5AF8;
    case 10: return lbl_806D5AF8;
    case 11: return lbl_806D5B50;
    case 12: return lbl_806D5AF8;
    default: return lbl_806D5AB8;
    }
}

float KartCharacterParam_GetVfxBindHeightOffset(const KartCharacterView* self)
{
    switch (self->characterId) {
    case 0: return lbl_806D5ACC;
    case 1: return lbl_806D5ACC;
    case 2: return lbl_806D5ACC;
    case 3: return lbl_806D5B1C;
    case 4: return lbl_806D5B1C;
    case 5: return lbl_806D5B1C;
    case 6: return lbl_806D5ACC;
    case 7: return lbl_806D5B20;
    case 8: return lbl_806D5ACC;
    case 9: return lbl_806D5ACC;
    case 10: return lbl_806D5ACC;
    case 11: return lbl_806D5ACC;
    case 12: return lbl_806D5ACC;
    default: return lbl_806D5AC8;
    }
}

float KartCharacterParam_GetKinopioBoostBonus(const KartCharacterView* self)
{
    switch (self->characterId) {
    case 0: return lbl_806D5AB8;
    case 1: return lbl_806D5AB8;
    case 2: return lbl_806D5AB8;
    case 3: return lbl_806D5AB8;
    case 4: return lbl_806D5AB8;
    case 5: return lbl_806D5AEC;
    case 6: return lbl_806D5AB8;
    case 7: return lbl_806D5AB8;
    case 8: return lbl_806D5AB8;
    case 9: return lbl_806D5AB8;
    case 10: return lbl_806D5AB8;
    case 11: return lbl_806D5AB8;
    case 12: return lbl_806D5AB8;
    default: return lbl_806D5AC8;
    }
}

int KartCharacterParam_GetIdentityIndex(const KartCharacterView* self)
{
    switch (self->characterId) {
    case 0: return 0;
    case 1: return 1;
    case 2: return 2;
    case 3: return 3;
    case 4: return 4;
    case 5: return 5;
    case 6: return 6;
    case 7: return 7;
    case 8: return 8;
    case 9: return 9;
    case 10: return 10;
    case 11: return 11;
    case 12: return 12;
    default: return 0;
    }
}
