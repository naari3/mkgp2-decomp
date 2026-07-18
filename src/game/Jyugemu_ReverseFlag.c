typedef unsigned char u8;

typedef struct JyugemuReverseFlag {
    void *jobj;
    int field_4;
    u8 state;
    u8 pad_9[3];
    int timer;
    float field_10;
} JyugemuReverseFlag;

extern void fn_8016C510(int state);
extern int Object_RenderJObjTree(void *jobj, int flags);
extern u8 lbl_806CEFC0[8];
extern const float lbl_806D3078;

#pragma exceptions on
void Jyugemu_ReverseFlag_SetState(JyugemuReverseFlag *self, u8 state) {
    if (state == 1) {
        if (--self->timer <= 0) {
            /* transition now */
        } else {
            return;
        }
    } else {
        self->timer = 180;
    }

    if (state == 1) {
        fn_8016C510(1);
    } else {
        fn_8016C510(0);
    }
    self->state = state;
}

int Jyugemu_ReverseFlag_Render(JyugemuReverseFlag *self) {
    void *jobj = self->jobj;
    if (jobj == 0) {
        return 0;
    }
    if (self->field_10 >= lbl_806D3078) {
        return 0;
    }
    if (lbl_806CEFC0[0] == 0) {
        return 0;
    }
    Object_RenderJObjTree(jobj, 7);
    return 1;
}
#pragma exceptions reset
