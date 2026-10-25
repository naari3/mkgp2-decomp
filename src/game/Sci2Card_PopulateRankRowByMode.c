extern unsigned char fn_801D5B8C(void *data, int key, int rank, int kind);

extern int g_gameMode;
extern unsigned char g_playerData[];
extern unsigned char lbl_805D275C[];

/* 0x800997E4: fill the receipt rank row flags (1..8) from the player
 * data of the current mode. */
void Sci2Card_PopulateRankRowByMode(int *key, unsigned char *ranks, unsigned char *mode)
{
    unsigned char *alt = lbl_805D275C;
    unsigned char *data = g_playerData;
    int i;

    for (i = 0; i < 8; i++) {
        ranks[i] = 0;
    }
    if (g_gameMode != 0) {
        int k = *(int *)(alt + 0x1D4);
        unsigned char m = alt[0x1D8];
        int r;

        *key = k;
        for (r = 1; r <= 8; r++) {
            if (fn_801D5B8C(alt, k, r, m == 0 ? 3 : 7) == 1) {
                ranks[r - 1] = 1;
            }
        }
        *mode = m;
    } else {
        int k = *(int *)(data + 0x1D4);
        unsigned char m = data[0x1D8];
        int r;

        *key = k;
        for (r = 1; r <= 8; r++) {
            if (fn_801D5B8C(data, k, r, m == 0 ? 3 : 7) == 1) {
                ranks[r - 1] = 1;
            }
        }
        *mode = m;
    }
}
