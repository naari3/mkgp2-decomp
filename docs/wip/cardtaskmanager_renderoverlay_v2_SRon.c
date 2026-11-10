/* CardTaskManager_RenderOverlay @ 0x80089C58: card task progress overlay.
 * While the current task is busy it shows a spinner; when it is done (or
 * no task is current) it lists every task with its status line. */

class CardTask {
public:
    virtual unsigned char IsDone(void);
    virtual void v0C(void);
    virtual void v10(void);
    virtual void Render(void);
    int kind;
};

struct CardTaskEntry {
    CardTask *task;
    int desc;
};

struct CardTaskManager {
    CardTaskEntry *entries;
    int count;
    int current;
    int frame;
};

struct CardTaskDesc {
    int id;
    const char *text;
};

extern "C" {
extern void TexMgr_DrawText_Format_Variant2(int layer, float x, float y, const char *fmt, ...);
extern void fn_8011F994(int layer);

extern const char lbl_806D32CC[5]; /* spinner chars */
extern const char lbl_806D32DC[3]; /* "%c" */
extern const char lbl_806D32E0[6];
extern const char lbl_806D32EC[3]; /* "%s" */
extern float lbl_806D32D4;
extern float lbl_806D32D8;
extern float lbl_806D32E8;
extern float lbl_806D32F0;
extern float lbl_806D32F4;
extern char Card_rodata_80312850[];          /* .rodata string pool base */
extern CardTaskDesc lbl_803FE7E8[];

void CardTaskManager_RenderOverlay(CardTaskManager *m);
}

#pragma exceptions on
void CardTaskManager_RenderOverlay(CardTaskManager *m) {
    char *pool = Card_rodata_80312850;

    if (m->current < m->count) {
        CardTask *t = m->entries[m->current].task;
        if (t != 0) {
            TexMgr_DrawText_Format_Variant2(1, lbl_806D32D4, lbl_806D32D8, lbl_806D32DC,
                                            lbl_806D32CC[(m->frame >> 4) % 4U]);
            if (t->IsDone() == 1) {
                t->Render();
                for (int i = 0; i < 8; i++) {
                    fn_8011F994(7 - i);
                }
                return;
            }
        }
    }

    const char **names = (const char **)(pool + 0xC);
    for (int i = 0; i < m->count; i++) {
        CardTaskEntry *e = &m->entries[i];
        CardTask *t = e->task;
        const char *desc = lbl_803FE7E8[e->desc].text;
        const char *name = names[t->kind];
        if (i > m->current) {
            name = lbl_806D32E0;
        }
        TexMgr_DrawText_Format_Variant2(1, lbl_806D32E8, 0x3C + i * 0x26, lbl_806D32EC, desc);
        TexMgr_DrawText_Format_Variant2(1, lbl_806D32F0, 0x3C + i * 0x26, lbl_806D32EC, name);
        TexMgr_DrawText_Format_Variant2(1, lbl_806D32F4, lbl_806D32F4, pool + 0x574);
        TexMgr_DrawText_Format_Variant2(1, lbl_806D32F4, lbl_806D32D8, pool + 0x584);
        if (i == m->current) {
            t->Render();
        }
        for (int j = 0; j < 8; j++) {
            fn_8011F994(j);
        }
    }
}
#pragma exceptions reset
