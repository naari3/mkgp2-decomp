extern int g_spriteSystemInited;

int SpriteSystem_EnsureInit(void) {
    if (g_spriteSystemInited != -1) {
        return 1;
    }
    g_spriteSystemInited = 0;
    return 1;
}
