/*
 * CardTaskManager overlay: while the current card task runs, a spinner;
 * once it reports done (or with no current task) the full task list with
 * per-task status strings.
 */
#pragma cplusplus on

extern "C" {
extern void TexMgr_DrawText_Format_Variant2(int layer, float x, float y, const char *fmt, ...);
extern void fn_8011F994(int layer);

extern char lbl_806D32CC[5];
extern char lbl_806D32DC[3];
extern char lbl_806D32E0[6];
extern char lbl_806D32EC[3];
extern unsigned int lbl_806D32D4;
extern unsigned int lbl_806D32D8;
extern unsigned int lbl_806D32E8;
extern unsigned int lbl_806D32F0;
extern unsigned int lbl_806D32F4;
extern unsigned int Card_rodata_80312850[];
extern unsigned int g_cardTaskFactories[];
}

#define CTM_F(x) (*(float *)&(x))

struct CardTask {
    virtual unsigned char IsDone();
    virtual void m0C();
    virtual void m10();
    virtual void Render();
    int status;
};

struct CardTaskEntry {
    CardTask *task;
    int name;
};

struct CardTaskName {
    int id;
    const char *name;
};

struct CardTaskManager {
    CardTaskEntry *entries;
    int count;
    int cur;
    int frame;
};

#pragma exceptions on
#pragma use_lmw_stmw on
extern "C" void CardTaskManager_RenderOverlay(CardTaskManager *m) {
    char *base = (char *)Card_rodata_80312850;
    CardTask *t;
    int i;
    int j;
    int y;
    int off;
    const char **stTbl;

    if (m->cur < m->count) {
        t = m->entries[m->cur].task;
        if (t) {
            TexMgr_DrawText_Format_Variant2(1, CTM_F(lbl_806D32D4), CTM_F(lbl_806D32D8), lbl_806D32DC,
                                            lbl_806D32CC[(m->frame >> 4) & 3u]);
            if (t->IsDone() == 1) {
                t->Render();
                for (i = 0; i < 8; i++) {
                    fn_8011F994(7 - i);
                }
                return;
            }
        }
    }
    stTbl = (const char **)(base + 0xC);
    for (i = 0, off = 0, y = 0x3C; i < m->count; i++, off += 8, y += 0x26) {
        CardTaskEntry *e = (CardTaskEntry *)((char *)m->entries + off);
        const char *st;
        const char *name;
        t = e->task;
        name = ((CardTaskName *)g_cardTaskFactories)[e->name].name;
        st = stTbl[t->status];
        if (i > m->cur) {
            st = lbl_806D32E0;
        }
        TexMgr_DrawText_Format_Variant2(1, CTM_F(lbl_806D32E8), (float)y, lbl_806D32EC, name);
        TexMgr_DrawText_Format_Variant2(1, CTM_F(lbl_806D32F0), (float)y, lbl_806D32EC, st);
        TexMgr_DrawText_Format_Variant2(1, CTM_F(lbl_806D32F4), CTM_F(lbl_806D32F4), base + 0x574);
        TexMgr_DrawText_Format_Variant2(1, CTM_F(lbl_806D32F4), CTM_F(lbl_806D32D8), base + 0x584);
        if (i == m->cur) {
            t->Render();
        }
        for (j = 0; j < 8; j++) {
            fn_8011F994(j);
        }
    }
}
#pragma use_lmw_stmw reset
#pragma exceptions reset
