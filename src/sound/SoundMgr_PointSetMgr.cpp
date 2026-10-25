/*
 * 0x8016CB44..0x8016CBAC: global ambience point set accessor / teardown.
 */

extern "C" {
void MemoryManager_Free(void *);
}

struct AmbPointSet {
    int count;
    void *points;

    ~AmbPointSet() {
        if (points) {
            MemoryManager_Free(points);
        }
        count = 0;
        points = 0;
    }
};

extern "C" {

extern AmbPointSet *lbl_806D15C8;

AmbPointSet *fn_8016CB44(void) {
    return lbl_806D15C8;
}

void fn_8016CB4C(void) {
    if (lbl_806D15C8) {
        delete lbl_806D15C8;
        lbl_806D15C8 = 0;
    }
}

}
