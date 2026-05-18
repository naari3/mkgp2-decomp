typedef struct KartBody KartBody;

/* Sets the warp-transit flag at KartBody+0xD2. When the flag becomes 1,
 * also writes -1 to the u32 field at +0x13C (likely a timer/cooldown reset).
 * The compare reads back the just-stored byte (lbz after stb) rather than
 * using the parameter directly, matching the field semantics. */
void KartBody_SetWarpTransitFlag(KartBody *self, unsigned char value) {
    *(unsigned char *)((char *)self + 0xd2) = value;
    if (*(unsigned char *)((char *)self + 0xd2) == 1) {
        *(int *)((char *)self + 0x13c) = -1;
    }
}
