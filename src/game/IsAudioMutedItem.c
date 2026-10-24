extern int lbl_802EDCA4[6];

int IsAudioMutedItem(void *self, int id) {
    int *p = lbl_802EDCA4;
    int i;

    for (i = 0; i < 6; i++, p++) {
        if (id == *p) {
            return 0;
        }
    }
    return 1;
}
