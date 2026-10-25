struct StepSeq {
    void Add(void *step, int time);
};

struct Obj801FA864 {
    char pad_0[0x48];
    Obj801FA864(int a, int b);
};

extern "C" {
extern int lbl_803BFF40[];
extern int lbl_806D00C8;
extern int lbl_806D00D0;
int Sci2Card_GetUnpackStatusCode(void);
unsigned char ServiceValue_Get(void);
void *fn_801F4DC0(void *seq, int id);

void *fn_801FB634(int arg);
char *fn_801FE404(void);
void fn_801FEF18(void *obj, int arg);
void *fn_801FF00C(int a, int b);
void *fn_8020007C(int a, int b, int c);
void *fn_802011D0(int a, int b);
void fn_80203F5C(int arg);
void fn_8020A7CC(void *fade, int a, int b, int c);
void *fn_80271340(void *p, int a, void *b, void *c, int d);
}

struct CardScene {
    char pad_0[0x10];
    StepSeq *seq;
    void *fade;
    int state;
};

extern "C" void fn_801FA864(CardScene *self) {
    int mode;
    void *p;

    if (ServiceValue_Get()) {
        fn_8020A7CC(self->fade, 0, 0x78, 0x78);
        fn_80203F5C(9);
        self->state = 1;
        return;
    }
    mode = *(int *)(fn_801FE404() + 0x16C);
    {
        StepSeq *seq = self->seq;
        seq->Add(fn_801FF00C(0, 8), 0);
    }
    p = fn_801F4DC0(self->seq, 8);
    if (p != 0) {
        fn_801FEF18(fn_80271340(p, 0, &lbl_806D00D0, &lbl_806D00C8, 0), lbl_803BFF40[0] + 1);
    }
    {
        StepSeq *seq = self->seq;
        seq->Add(fn_8020007C(0, 0, 9), 0x32);
    }
    {
        StepSeq *seq = self->seq;
        seq->Add(fn_802011D0(0, 0xA), 0x32);
    }
    if (mode == 2) {
        StepSeq *seq = self->seq;
        seq->Add(fn_801FB634(2), 0x28);
    } else if (Sci2Card_GetUnpackStatusCode() == 5) {
        /* Reusing the dead mode slot reproduces the original register choice. */
        mode = (int)self->seq;
        ((StepSeq *)mode)->Add(new Obj801FA864(0, 4), 0x28);
    } else {
        StepSeq *seq = self->seq;
        seq->Add(fn_801FB634(2), 0x28);
    }
    fn_8020A7CC(self->fade, 0, 0x3C, 0x3C);
    self->state = 2;
}
