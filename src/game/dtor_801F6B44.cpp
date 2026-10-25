/* Shared palette handle: releases the TEX palette when the last reference goes away. */
extern "C" {
extern void *lbl_804E5508[];
void TEXReleasePalette(void **palette);
}

struct PaletteRef {
    void *vt;
    void *palette;
    int refs;

    ~PaletteRef();
};

PaletteRef::~PaletteRef() {
    vt = lbl_804E5508;
    refs--;
    if (refs <= 0 && palette != 0) {
        TEXReleasePalette(&palette);
        palette = 0;
    }
}
