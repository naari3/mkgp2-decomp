extern int g_earnedCoins;
extern int g_extraCoinsToAdd;

void AddCoinsFromExtraStage(void) {
    int total;
    if (g_extraCoinsToAdd < 0) {
        g_extraCoinsToAdd = 0;
    }
    total = g_earnedCoins;
    total += g_extraCoinsToAdd;
    g_earnedCoins = total;
}
