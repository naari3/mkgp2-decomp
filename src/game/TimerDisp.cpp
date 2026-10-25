/*
 * 0x802321D4..0x80232884: clTimerDisp, the countdown clock (pulsing ring
 * sprites 0xA3..0xA6 plus a two-digit number) shown in the corner of the
 * card / continue screens.
 */

void *operator new(unsigned long size);
void operator delete(void *p) throw();

struct Sprite {
    int id;
    int prio;
    int i8;
    float x, y;
    float sx, sy;
    float f1C;
    float alpha;
    char pad24[0xC];
    Sprite(int id, int a, int b);
    ~Sprite();
    void SetPos(float px, float py) {
        x = px;
        y = py;
    }
};

extern "C" {
void fn_801A0004(Sprite *s);
void fn_8019FF6C(Sprite *s, int on);
short *fn_801A0310(Sprite *s, int ch);
void Sprite_SetAnimTime(Sprite *s, float t);
void SoundMgr_Play(int id);
}

class clTimerDisp {
public:
    int prio;
    int digitSet;
    int ring;
    int markSec;
    int sec;
    int prevSec;
    float time;
    float x, y;
    unsigned char visible;
    Sprite *rings[4];
    Sprite *digitSpr[3];
    short *digits[3][2];

    clTimerDisp();
    ~clTimerDisp();
    void Reset();
    void Draw();
    void SetTime(float t);
};

void clTimerDisp::Reset() {
    SetTime(-1.0f);
}

void clTimerDisp::Draw() {
    if (sec >= 0) {
        rings[ring]->prio = prio;
        fn_801A0004(rings[ring]);
        digitSpr[digitSet]->prio = prio;
        fn_801A0004(digitSpr[digitSet]);
    }
}

void clTimerDisp::SetTime(float t) {
    if (t < 0.0f) {
        time = -1.0f;
        prevSec = -1;
        sec = -1;
        digitSet = 2;
        ring = 3;
        markSec = -1;
        return;
    }
    time = t;
    prevSec = sec;
    sec = (int)time;
    if (sec >= 10) {
        digitSet = 0;
    } else if (sec >= 6) {
        digitSet = 1;
    } else {
        digitSet = 2;
    }
    if (ring <= 1) {
        if (sec <= 5) {
            ring = 2;
            markSec = sec;
            Sprite_SetAnimTime(rings[ring], 0.0f);
        }
    } else if (ring >= 2 && sec > 5) {
        ring = 0;
        markSec = sec;
        Sprite_SetAnimTime(rings[ring], 0.0f);
    }
    if (ring % 2 == 0 && markSec - sec > 0) {
        ring++;
    }
    if (sec <= 5 && prevSec > sec) {
        SoundMgr_Play(3);
    }
    short *p = digits[digitSet][0];
    if (p) {
        int base = 0x1842;
        if (digitSet == 2) {
            base = 0x184C;
        }
        *p = base + sec % 10;
    }
    p = digits[digitSet][1];
    if (p) {
        *p = sec / 10 + 0x1842;
    }
    rings[ring]->SetPos(x, y);
    digitSpr[digitSet]->SetPos(x, 8.0f + y);
    float f = 1.0f - (time - sec);
    Sprite_SetAnimTime(rings[ring], f);
    Sprite_SetAnimTime(digitSpr[digitSet], f);
}

clTimerDisp::~clTimerDisp() {
    int i;
    for (i = 0; i < 4; i++) {
        if (rings[i]) {
            delete rings[i];
            rings[i] = 0;
        }
    }
    for (i = 0; i < 3; i++) {
        if (digitSpr[i]) {
            delete digitSpr[i];
            digitSpr[i] = 0;
        }
    }
}

clTimerDisp::clTimerDisp() {
    prio = 4;
    digitSet = 2;
    ring = 3;
    markSec = -1;
    sec = -1;
    prevSec = -1;
    time = -1.0f;
    visible = 1;
    x = 584.0f;
    y = 56.0f;
    rings[0] = new Sprite(0xA6, 1, 0);
    rings[1] = new Sprite(0xA5, 1, 0);
    rings[2] = new Sprite(0xA4, 1, 0);
    rings[3] = new Sprite(0xA3, 1, 0);
    digitSpr[0] = new Sprite(0xA2, 1, 0);
    digitSpr[1] = new Sprite(0xA1, 1, 0);
    digitSpr[2] = new Sprite(0xA0, 1, 0);
    fn_8019FF6C(rings[1], 1);
    fn_8019FF6C(rings[3], 1);
    rings[0]->SetPos(x, y);
    rings[1]->SetPos(x, y);
    rings[2]->SetPos(x, y);
    rings[3]->SetPos(x, y);
    digitSpr[0]->SetPos(x, 8.0f + y);
    digits[0][0] = 0;
    digits[0][1] = 0;
    digitSpr[1]->SetPos(x, 8.0f + y);
    digits[1][0] = 0;
    digits[1][1] = 0;
    digitSpr[2]->SetPos(x, 8.0f + y);
    digits[2][0] = 0;
    digits[2][1] = 0;
    digits[0][0] = fn_801A0310(digitSpr[0], 0x1842);
    digits[0][1] = fn_801A0310(digitSpr[0], 0x1843);
    digits[1][0] = fn_801A0310(digitSpr[1], 0x1842);
    digits[2][0] = fn_801A0310(digitSpr[2], 0x184C);
}
