/*
 * 0x80163614..0x801636B4: factory for the loader holder (vtable
 * lbl_80490DAC, base vtable lbl_8048FF80 / base dtor dtor_801577D4).
 * Real C++ new-expressions so CW emits the DELETEPOINTER / DESTROYBASE
 * extab actions; mangled names are bridged in tools/extab_user_renames.json.
 */

struct CourseLoader {
    char _opaque[0x5C];
    CourseLoader(void *desc, int mode);
};

struct LoaderBase {
    LoaderBase() {}
    virtual ~LoaderBase();
};

struct LoaderHolder : LoaderBase {
    CourseLoader *loader;
    unsigned char done;

    LoaderHolder(void *desc) {
        done = 0;
        loader = new CourseLoader(desc, 0);
        if (loader == 0) {
            done = 1;
        }
    }
    virtual void vKeyFunction();
};

#pragma exceptions on

extern "C" LoaderHolder *fn_80163614(void *desc) {
    return new LoaderHolder(desc);
}

#pragma exceptions reset
