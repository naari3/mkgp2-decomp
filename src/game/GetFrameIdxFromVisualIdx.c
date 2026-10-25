int GetFrameIdxFromVisualIdx(void *self, int visualIdx) {
    int frame = 0;
    if (visualIdx == 0) {
        frame = 0;
    } else if (visualIdx == 1) {
        frame = 1;
    } else if (visualIdx == 2) {
        frame = 8;
    } else if (visualIdx == 3) {
        frame = 11;
    } else if (visualIdx == 4) {
        frame = 3;
    } else if (visualIdx == 5) {
        frame = 7;
    } else if (visualIdx == 6) {
        frame = 10;
    } else if (visualIdx == 7) {
        frame = 12;
    } else if (visualIdx == 8) {
        frame = 9;
    } else if (visualIdx == 9) {
        frame = 5;
    } else if (visualIdx == 10) {
        frame = 2;
    } else if (visualIdx == 11) {
        frame = 6;
    } else if (visualIdx == 12) {
        frame = 4;
    }
    return frame;
}
