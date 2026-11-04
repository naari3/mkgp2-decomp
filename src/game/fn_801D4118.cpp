/* Copy player unlocks and course progress into the selection screen snapshot. */
struct UnlockPlayerView {
    unsigned short values[6];
    unsigned char flag;
    char pad0D[2];
    unsigned char courses[6][4];
    unsigned char extra[6][4];
    char pad3F;
    int clearCount;
    char pad44[0x16C - 0x44];
    unsigned char tail0, tail1;
};
struct UnlockSnapshot {
    unsigned short values[6];
    short pad0C, field0E, field10;
    char pad12[0xE4 - 0x12];
    unsigned char fieldE4;
    char padE5[0x152 - 0xE5];
    unsigned char field152;
    char pad153[0x198 - 0x153];
    unsigned char tail0, tail1, pad19A, titleKind;
    char pad19C[0x1B1 - 0x19C];
    unsigned char titleResult;
    char pad1B2[6];
    unsigned char flag;
    char pad1B9;
    unsigned char progressA[8], progressB[8], progressC[8];
};
struct RankLog;
extern "C" {
int Items_ResolveOwnedAlias(UnlockPlayerView *, int);
unsigned char Items_PlayerOwnsAnyAlias(UnlockPlayerView *, int, unsigned char);
int ItemAlias_DestToSource(int, unsigned char *);
void fn_801D5F74(UnlockSnapshot *, int, int);
extern RankLog *lbl_806D10A0;
unsigned char get_title_result(RankLog *, int *, int *, int *);
}
static inline RankLog *GetSnapshotRankLog() {
    return lbl_806D10A0 == 0 ? (RankLog *)0 : lbl_806D10A0;
}
extern "C" int fn_801D4118(UnlockSnapshot *self, UnlockPlayerView *player) {
    if (player == 0) return 0;
    self->values[0] = player->values[0];
    self->values[1] = player->values[1];
    self->values[2] = player->values[2];
    self->values[3] = player->values[3];
    self->values[4] = player->values[4];
    self->values[5] = player->values[5];
    self->flag = player->flag;
    for (int i = 0; i < 60; i++) {
        int item = Items_ResolveOwnedAlias(player, i);
        if (Items_PlayerOwnsAnyAlias(player, item, 1) == 1) {
            fn_801D5F74(self, ItemAlias_DestToSource(item, 0), 0);
        }
    }
    int course;
    self->field152 = self->fieldE4 = course = 0;
    if (player->clearCount >= 1) {
        for (int i = 0; i < 6; i++) {
            self->progressA[i] = 5;
            self->progressB[i] = 5;
        }
        if (player->clearCount >= 3) {
            for (int i = 0; i < 6; i++) self->progressC[i] = 5;
        } else if (player->clearCount >= 2) {
            for (; course < 6; course++) {
                int progress;
                for (progress = 0; progress < 4; progress++) {
                    if (player->courses[course][progress] == 0) break;
                }
                self->progressC[course] = progress;
            }
        }
    } else {
        for (; course < 6; course++) {
            int progress;
            for (progress = 0; progress < 4; progress++) {
                if (player->courses[course][progress] == 0) break;
            }
            if (player->extra[course][0]) progress = 5;
            self->progressB[course] = progress;
            self->progressA[course] = progress;
        }
    }
    self->progressA[5] = 0;
    self->progressB[5] = 0;
    self->progressC[5] = 0;
    self->field0E = 0;
    self->field10 = 0;
    int a = 0;
    int b = 0;
    int c = 0;
    get_title_result(GetSnapshotRankLog(), &a, &b, &c);
    self->titleKind = 0x71;
    self->titleResult = c;
    self->tail0 = player->tail0;
    self->tail1 = player->tail1;
    return 1;
}
