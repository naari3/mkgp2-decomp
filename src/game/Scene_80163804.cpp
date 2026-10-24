/*
 * 0x80163804..0x801638B4: factory for the course loader scene (vtable
 * lbl_80490DF8, scene base vtable lbl_803FE0C8 / base dtor dtor_8007D0D4).
 * Real C++ new-expressions so CW emits the DELETEPOINTER / DESTROYBASE
 * extab actions; mangled names are bridged in tools/extab_user_renames.json.
 */

struct CourseLoader {
    char _opaque[0x5C];
    CourseLoader(void *desc, void *arg);
};

struct SceneBase {
    virtual ~SceneBase();
    SceneBase() { done = 0; }

    unsigned char done;
};

struct CourseLoadScene : SceneBase {
    CourseLoader *loader;

    CourseLoadScene(void *desc, void *arg) {
        done = 0;
        loader = new CourseLoader(desc, arg);
        if (loader == 0) {
            done = 1;
        }
    }
    virtual void vKeyFunction();
};

#pragma exceptions on

extern "C" CourseLoadScene *fn_80163804(void *desc, void *arg) {
    return new CourseLoadScene(desc, arg);
}

#pragma exceptions reset
