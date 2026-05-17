typedef struct KartMovement KartMovement;

void KartMovement_SetRemainingLaps(KartMovement *km, int laps) {
    *(int *)((char *)km + 0x240) = (laps < 0) ? 0 : laps;
}
