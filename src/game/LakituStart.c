typedef struct LakituStart LakituStart;

void LakituStart_SetCountdownHoldFrames(LakituStart *self, int frames) {
    *(int *)((char *)self + 0x54) = frames;
}
