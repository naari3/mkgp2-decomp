extern void *PathFollower_EnsureGlobalAlloc(void);
extern void fn_801DC510(void *pf, int arg);
extern void fn_801E6E4C(void *kart, int arg);
extern void *Read_U32[8];
extern int g_gameMode;

void fn_801EB91C(void *self, int arg) {
    int i;

    if (g_gameMode != 1) {
        for (i = 0; i < 8; i++) {
            if (Read_U32[i] != 0) {
                fn_801E6E4C(Read_U32[i], arg);
            }
        }
        fn_801DC510(PathFollower_EnsureGlobalAlloc(), 0);
    }
}
