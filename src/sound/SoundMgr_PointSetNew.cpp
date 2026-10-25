/*
 * 0x8016CBAC..0x8016CC04: lazy creation of the global ambience point set.
 */

extern "C" {
void MemoryManager_Free(void *);
}

struct SpawnEntry;

struct AmbPointSet {
    int count;
    void *points;

    AmbPointSet(SpawnEntry *table);
};

extern "C" {

extern AmbPointSet *lbl_806D15C8;

void fn_8016CBAC(SpawnEntry *table) {
    if (lbl_806D15C8 == 0) {
        lbl_806D15C8 = new AmbPointSet(table);
    }
}

}
