typedef struct SpawnTableEntry SpawnTableEntry;

/* SpawnTable terminator predicate.
 * Checks bit 1 (mask 0x2) of flags field at +0xC.
 * Returns 0 or 1. */
unsigned int IsSpawnTableTerminator(SpawnTableEntry *entry) {
    return (*(unsigned int *)((char *)entry + 0xc) >> 1) & 1;
}
