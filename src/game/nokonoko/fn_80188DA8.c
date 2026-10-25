typedef struct NokoNode {
    struct NokoNode *next;
} NokoNode;

extern NokoNode *g_nokonokoHead;
extern int lbl_806D1684;
extern unsigned char g_nokonokoEnable;
extern float lbl_806D168C;
extern void *lbl_80677EC8[4];
extern float lbl_80677ED8[4];
extern unsigned int OSGetTick(void);
extern void MemoryManager_TimedFree(void *p);
extern void Object_DtorWithGXSync(void *obj, int flag);

void fn_80188DA8(void) {
    int i;
    unsigned int t;
    if (g_nokonokoEnable) {
        while (g_nokonokoHead != 0) {
            NokoNode *n = g_nokonokoHead;
            g_nokonokoHead = n->next;
            if (n != 0) {
                MemoryManager_TimedFree(n);
            }
        }
        for (i = 0; i < 4; i++) {
            if (lbl_80677EC8[i] != 0) {
                Object_DtorWithGXSync(lbl_80677EC8[i], 1);
            }
        }
    }
    lbl_80677EC8[0] = 0;
    g_nokonokoHead = 0;
    lbl_80677EC8[1] = 0;
    lbl_80677EC8[2] = 0;
    lbl_80677EC8[3] = 0;
    t = OSGetTick() / (*(unsigned int *)0x800000F8 / 4);
    g_nokonokoEnable = 0;
    lbl_80677ED8[0] = 0.0f;
    lbl_80677ED8[1] = 0.0f;
    lbl_80677ED8[2] = 0.0f;
    lbl_806D168C = 0.0f;
    lbl_806D1684 = (int)t % 64;
}
