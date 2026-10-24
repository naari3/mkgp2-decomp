#pragma cplusplus on
struct HitMessageSprite {
    virtual void Destroy(int);
};

extern "C" {
extern unsigned char lbl_806D1478;
extern HitMessageSprite *lbl_806D148C;
extern HitMessageSprite *lbl_806D1490;
extern void fn_80120A08(int);

int HitMessageOverlay_Destroy(void)
{
    if (lbl_806D1478 == 0) {
        return 0;
    }
    if (lbl_806D1490 != 0) {
        lbl_806D1490->Destroy(1);
    }
    if (lbl_806D148C != 0) {
        lbl_806D148C->Destroy(1);
    }
    lbl_806D1490 = 0;
    lbl_806D148C = 0;
    lbl_806D1478 = 0;
    fn_80120A08(0xC6C);
    fn_80120A08(0xC6D);
    fn_80120A08(0xC6E);
    return 1;
}
}
#pragma cplusplus off
