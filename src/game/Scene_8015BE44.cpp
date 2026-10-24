/*
 * 0x8015BE44..0x8015BED4: factory for the debug model viewer scene (vtable
 * lbl_80490064, scene base vtable lbl_803FE0C8 / base dtor dtor_8007D0D4).
 * Real C++ new-expression + inline ctors for the DELETEPOINTER /
 * DESTROYBASE extab actions; mangled names are bridged in
 * tools/extab_user_renames.json.
 */

typedef struct ViewerModelEntry {
    int resId;
    float scale;
    char pad[0x1C];
} ViewerModelEntry;

extern "C" {
extern ViewerModelEntry lbl_80368074[];
extern int lbl_806D1594;
extern int lbl_806D1598;
extern int lbl_806D159C;
extern int lbl_806D15A0;
extern float lbl_806D15A4;
extern float lbl_806D15A8;
extern void fn_80121210(void);
extern void fn_8015BCC4(int resId, float scale);
}

struct SceneBase {
    virtual ~SceneBase();
    SceneBase() { done = 0; }

    unsigned char done;
};

struct ViewerScene : SceneBase {
    ViewerScene() {
        fn_80121210();
        lbl_806D1594 = 0;
        lbl_806D1598 = 0;
        lbl_806D159C = 0;
        lbl_806D15A0 = 0;
        fn_8015BCC4(lbl_80368074[0].resId, lbl_80368074[0].scale);
        lbl_806D15A8 = lbl_806D15A4 = 0.0f;
    }
    virtual void vKeyFunction();
};

#pragma exceptions on

extern "C" ViewerScene *fn_8015BE44(void) {
    return new ViewerScene;
}

#pragma exceptions reset
