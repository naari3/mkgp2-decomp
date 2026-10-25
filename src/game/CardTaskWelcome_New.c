extern void *Alloc(unsigned long size);

typedef struct CardTaskCallback {
    int a;
    int b;
    int c;
} CardTaskCallback;

typedef struct CardTaskWelcome {
    void **vtbl;
    int state;
    CardTaskCallback step;
    int result;
    unsigned char pad_18[4];
} CardTaskWelcome;

extern void *lbl_803FE898[];
extern void *lbl_803FE8B8[];
extern CardTaskCallback lbl_803F1C68;

/* 0x8008A2A0: allocate and construct the welcome card task. */
CardTaskWelcome *CardTaskWelcome_New(void)
{
    CardTaskWelcome *task = Alloc(sizeof(CardTaskWelcome));

    if (task != 0) {
        task->vtbl = lbl_803FE8B8;
        task->state = 0;
        task->vtbl = lbl_803FE898;
        task->step = lbl_803F1C68;
        task->result = 0;
    }
    return task;
}
