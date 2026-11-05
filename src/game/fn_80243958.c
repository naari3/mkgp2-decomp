extern "C" {
extern void PreloadResource(int);
extern void *GetEnemyParam(void);
extern int *AI_GetItemList(void *, int, int, int, int);
extern int fn_8023DBEC(int);
extern int g_gameMode, g_cupId, g_roundIndex;

void fn_80243958(void) {
    int round, cup, mode;
    int *items;
    int i;
    PreloadResource(0xC49);
    PreloadResource(0xC2E);
    PreloadResource(0xC2D);
    PreloadResource(0x1CD3);
    PreloadResource(0x1CD4);
    PreloadResource(0x1CD6);
    if (g_gameMode != 1) {
        for (i = 0; i < 5; ++i) {
            round = g_roundIndex;
            cup = g_cupId;
            mode = g_gameMode;
            items = AI_GetItemList(GetEnemyParam(), mode, cup, round, i);
            while (*items != -1) {
                PreloadResource(fn_8023DBEC(*items));
                ++items;
            }
        }
    }
}

}
