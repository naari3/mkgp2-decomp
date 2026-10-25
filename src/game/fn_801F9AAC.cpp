/* Frees the global model bank and every model pair it holds. */
struct GXObject {
    ~GXObject();
};

struct ModelPair {
    int id;
    GXObject *obj[2];

    ~ModelPair() {
        int i;

        for (i = 0; i < 2; i++) {
            if (obj[i]) {
                delete obj[i];
                obj[i] = 0;
            }
        }
    }
};

extern "C" {
extern const char lbl_803BFB08[];
void DebugPrintf(const char *fmt, ...);
}

struct ModelBank {
    ModelPair *pairs[13];

    ~ModelBank() {
        ModelPair *p;
        int i;

        for (i = 12; i >= 0; i--) {
            p = pairs[i];
            delete p;
            pairs[i] = 0;
        }
        DebugPrintf(lbl_803BFB08);
    }
};

extern "C" ModelBank *lbl_806D19B4;

extern "C" void fn_801F9AAC(void) {
    if (lbl_806D19B4) {
        delete lbl_806D19B4;
        lbl_806D19B4 = 0;
    }
}
