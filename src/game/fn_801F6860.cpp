/* Destructor of a palette holder with an owned buffer (base destructor inlined). */
extern "C" {
extern void *lbl_804E54FC[];
extern void *lbl_804E5508[];
void TEXReleasePalette(void **palette);
}

struct PaletteRef {
    void *vt;
    void *palette;
    int refs;

    ~PaletteRef() {
        vt = lbl_804E5508;
        refs--;
        if (refs <= 0 && palette != 0) {
            TEXReleasePalette(&palette);
            palette = 0;
        }
    }
};

struct PaletteBuffer : PaletteRef {
    int unkC;
    unsigned char *data;

    ~PaletteBuffer();
};

PaletteBuffer::~PaletteBuffer() {
    vt = lbl_804E54FC;
    if (data != 0) {
        delete[] data;
        data = 0;
    }
}
