#ifndef GAME_TYPES_YISTATE_H
#define GAME_TYPES_YISTATE_H

struct YIState {
    unsigned char a;
    float x04;
    unsigned char b;
    int x0c;
    unsigned char c;
    float x14;
    unsigned char d;
    float x1c;
    int x20;
    int x24;
    int x28;
    int x2c;

    YIState() {
        x20 = 0;
        x24 = 0;
        x2c = 0;
        a = 0;
        b = 0;
        c = 0;
        d = 0;
        x14 = 0.0f;
        x1c = 0.0f;
    }

    ~YIState() {
        if (a == 1) {
            fn_8016C394(0x3E);
        }
        if (d == 1) {
            fn_8016C394(0x3F);
        }
        if (c == 1) {
            fn_8016C394(0x40);
        }
        if (b == 1) {
            fn_8016C394(0x3B);
        }
    }

    template <int N>
    void UpdateT();

    void Update() {
        UpdateT<0>();
    }
};

#endif /* GAME_TYPES_YISTATE_H */
