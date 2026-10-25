/*
 * 0x801B85DC..0x801B87B0: creates the single popup sprite used by a
 * notice (kind 0x1B, 0xD or 0x15) and positions it.
 */

class Sprite {
public:
    Sprite(int id, int a, int b);
    char pad0[0xC];
    float x;
    float y;
    char pad14[4];
    float rot;
    char pad1C[0x30 - 0x1C];
    void SetPos(float px, float py) { x = px; y = py; }
    void SetRot(float r) { rot = r; }
};

extern "C" {
extern Sprite *lbl_806D180C;
extern int lbl_806D1810;
extern int lbl_806D1814;
extern unsigned char lbl_806D1818;
extern unsigned char lbl_806D1819;
extern short lbl_806D181A;
void Sprite_SetAnimParam(Sprite *sprite, short id, short value);
void fn_8019FF6C(Sprite *sprite, int on);
int fn_801B85DC(int kind, unsigned char alt, short param);
}

int fn_801B85DC(int kind, unsigned char alt, short param)
{
    if (lbl_806D180C != 0) {
        return 0;
    }
    lbl_806D1810 = 0;
    lbl_806D1814 = kind;
    lbl_806D1819 = alt;
    lbl_806D181A = param;
    if (kind == 0x1B) {
        if (alt) {
            lbl_806D180C = new Sprite(0x18E, 1, 0);
        } else {
            lbl_806D180C = new Sprite(0x184, 1, 0);
        }
        lbl_806D180C->SetPos(320.0f, 210.0f);
        lbl_806D180C->SetRot(0.0f);
        fn_8019FF6C(lbl_806D180C, 1);
        lbl_806D1818 = 2;
        return 1;
    }
    if (kind == 0xD) {
        Sprite *s = new Sprite(0x1C, 1, 0);
        lbl_806D180C = s;
        Sprite_SetAnimParam(s, 0x1D3E, param);
        lbl_806D180C->SetPos(320.0f, 348.0f);
    }
    if (kind == 0x15) {
        if (alt) {
            lbl_806D180C = new Sprite(0x18E, 1, 0);
        } else {
            lbl_806D180C = new Sprite(0x184, 1, 0);
        }
        lbl_806D180C->SetPos(320.0f, 191.0f);
    }
    lbl_806D1818 = 0;
    return 1;
}
