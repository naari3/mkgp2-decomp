/* Race scene per-player slot tables (car object, item select and slot id
 * for each of the 4 players). This TU owns their .bss. */
void *g_carObjects[4];
void *g_itemSelects[4];
int RaceScene_PlayerSlots_bss_805D2B00[4];

void *GetPlayerCarBySlot(int slot) {
    if (slot < 0 || slot >= 4) {
        return 0;
    }
    return g_carObjects[slot];
}

void RaceScene_ClearPlayerSlotPointers(void) {
    int i;

    for (i = 0; i < 4; i++) {
        g_carObjects[i] = 0;
        g_itemSelects[i] = 0;
        RaceScene_PlayerSlots_bss_805D2B00[i] = 0;
    }
}
