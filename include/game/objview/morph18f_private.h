/* Private views for the paired position morph buffers. */
typedef struct MorphAttr { int attr,unused,type,format; unsigned short unknown,stride; void *data; } MorphAttr;
typedef struct MorphHandle { char pad[8]; MorphAttr *attrs; } MorphHandle;
typedef struct MorphDObj { char pad8[8]; void *material; MorphHandle *handle; } MorphDObj;
typedef struct MorphVec { float x,y,z; } MorphVec;
typedef struct MorphNode { struct MorphNode *next; MorphDObj *obj[2]; MorphAttr *original[2]; MorphAttr *copy[2]; MorphVec *input[2]; unsigned short *indices[2]; MorphVec *output[2]; int count; } MorphNode;
typedef struct MorphView { void *vt,*model; float phase; MorphNode *head; } MorphView;
extern void *HSD_MemAlloc(unsigned int);
extern void HSD_Free(void *);
extern void *memcpy(void *,const void *,unsigned int);
extern MorphDObj *HSD_JObjGetDObj(void *);
extern int fn_8018387C(MorphHandle *);
extern unsigned char fn_80183538(MorphHandle *,int,void *,int);
extern unsigned char fn_80182ED0(MorphHandle *,int);
static inline void MorphClear(MorphNode *n) {
    n->obj[0]=0; n->original[0]=0; n->copy[0]=0; n->input[0]=0; n->output[0]=0; n->indices[0]=0;
    n->obj[1]=0; n->original[1]=0; n->copy[1]=0; n->input[1]=0; n->output[1]=0; n->indices[1]=0;
    n->count=0;
}
