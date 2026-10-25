typedef struct SpeedTable {
    void *pts;
    int count;
    float maxProgress;
    unsigned char pad[0xc];
} SpeedTable;

typedef struct KartMove {
    unsigned char pad0[8];
    int table;
    float progress;
    unsigned char pad10[0x24 - 0x10];
    SpeedTable *tables;
} KartMove;

void KartMovement_SetTravelProgress(KartMove *k, float p) {
    if (p > k->tables[k->table].maxProgress) {
        p = k->tables[k->table].maxProgress;
    }
    k->progress = p;
}
