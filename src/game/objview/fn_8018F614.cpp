struct HSD_JObj;
struct Pair { const char *a,*b; };
extern "C" {
extern int g_cupId,g_courseVariantIdx;
extern const char *lbl_806CFC58,*lbl_806CFC5C,*lbl_806CFC60;
extern const char lbl_80378210[];
extern const float lbl_806D94B8;
void DebugPrintf(const char *,...);
void fn_801825FC();
void fn_801825C8();
void fn_8018F7D4(void *,void *);
}
struct clNormal3D { char data[0x5c]; clNormal3D(const char *,int); };
extern "C" HSD_JObj *ResolveJointByName(clNormal3D *,const char *);
struct MorphNode { char data[0x38]; MorphNode(HSD_JObj *,HSD_JObj *); };
struct MorphBase { MorphBase() {} virtual ~MorphBase(); };
struct MorphView : MorphBase {
    clNormal3D *model;
    float phase;
    MorphNode *head;
    MorphView();
    virtual ~MorphView();
};
MorphView::MorphView() {
    const char *cursor=lbl_80378210;
    HSD_JObj *b;
    HSD_JObj *a;
    const char *name;
    const Pair *pairs;
    int count;
    DebugPrintf(cursor+0x2f4);
    model=0; head=0; phase=lbl_806D94B8;
    name=0; pairs=0; count=0;
    switch (g_cupId) {
    case 1:
        switch (g_courseVariantIdx) {
        case 0: name=lbl_806CFC58; pairs=(const Pair *)(cursor+0xcc); count=3; break;
        case 1: name=lbl_806CFC5C; pairs=(const Pair *)(cursor+0x1b4); count=3; break;
        case 2: name=lbl_806CFC60; pairs=(const Pair *)(cursor+0x29c); count=3; break;
        }
        break;
    case 9: name=lbl_806CFC58; pairs=(const Pair *)(cursor+0xcc); count=3; break;
    }
    if (!name || !pairs) return;
    fn_801825FC();
    model=new clNormal3D(name,0);
    fn_801825C8();
    cursor=(const char *)pairs;
    for (int i=0;i<count;i++,cursor+=8) {
        a=ResolveJointByName(model,((const Pair *)cursor)->a);
        b=ResolveJointByName(model,((const Pair *)cursor)->b);
        if (a && b) {
            MorphNode *n=new MorphNode(a,b);
            if (head) fn_8018F7D4(head,n);
            else head=n;
        }
    }
}
