typedef struct Obj {
    unsigned char pad0[0x58];
    float cur[4][4];
    float prev[4][4];
    float prev2[4][4];
} Obj;

void fn_8019CC2C(Obj *o) {
    int i;
    int j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            o->prev2[i][j] = o->cur[i][j];
        }
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            o->prev[i][j] = o->cur[i][j];
        }
    }
}
