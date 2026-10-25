/* 0x8015B70C..0x8015B790: debug model viewer draw callback. */

struct Viewer {
    virtual ~Viewer();
    virtual unsigned char IsReady();
    virtual void Draw();
};

extern "C" {
extern Viewer *lbl_806D1588;
extern void *lbl_806D158C;
extern void CObj_DebugVizPathFlush(Viewer *);
extern void Object_RenderJObjTree(void *, int);
extern void fn_8011FAB8(void);
extern void fn_802C14B8(int);

#pragma exceptions on

void fn_8015B70C(void) {
    if (lbl_806D1588 != 0 && lbl_806D158C != 0) {
        if (lbl_806D1588->IsReady() == 1) {
            CObj_DebugVizPathFlush(lbl_806D1588);
            Object_RenderJObjTree(lbl_806D158C, 7);
            lbl_806D1588->Draw();
        }
    }
    fn_8011FAB8();
    fn_802C14B8(-1);
}

#pragma exceptions reset
}
