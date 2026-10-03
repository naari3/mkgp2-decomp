/* Observed Normal3D loading fields and asset-row pointer layout only. */
typedef struct JObj JObj;
typedef struct AssetRow {
    void* descriptor;
    void** jointAnims;
    void** materialAnims;
    void** shapeAnims;
} AssetRow;
typedef struct PublicRows {
    AssetRow** rows;
} PublicRows;
typedef struct Normal3DLoadView {
    unsigned char pad00[3];
    unsigned char hasAnimations;
    unsigned char pad04[0x20];
    void* file;
    PublicRows* publicRows;
    JObj* root;
    void* model;
    AssetRow* selected;
    unsigned char pad38[8];
    JObj** table;
    int count;
} Normal3DLoadView;

extern void* FileLoader_Open(const char*);
extern void* Archive_GetCurrent(void*);
extern void* HSD_ArchiveGetPublicAddress(void*, const char*);
extern void clModelM_Construct(AssetRow*, void**, JObj**);
extern void clNormal3D_SetFlags(Normal3DLoadView*, unsigned int, JObj*);
extern JObj* HSD_JObjLoadDesc(void*);
extern int clNormal3D_CountJObjs(Normal3DLoadView*, JObj*, int);
extern void* FUN_8003b120(unsigned int);
extern int clNormal3D_FlattenJObjTree(JObj*, JObj**, int);
extern void DebugPrintf(const char*, ...);
extern const char lbl_802E97C4[];
extern const char lbl_802E97D0[];

static inline void* FirstAnimation(void** list)
{
    if (list == 0) return 0;
    return list[0];
}

int clNormal3D_Load(Normal3DLoadView* self, const char* path,
                    int slot, unsigned char construct)
{
    AssetRow** rows;
    AssetRow** cursor;
    int i;
    int flattened;
    if (self->root != 0) return 0;
    self->file = FileLoader_Open(path);
    if (self->file == 0) return 0;
    self->publicRows = (PublicRows*)HSD_ArchiveGetPublicAddress(
        Archive_GetCurrent(self->file), lbl_802E97C4);
    rows = self->publicRows->rows;
    if (rows == 0) return 0;
    for (cursor = rows, i = 0; i < slot; ++i, ++cursor) {
        if (*cursor == 0) return 0;
    }
    self->selected = rows[slot];
    if (construct == 1) {
        clModelM_Construct(self->selected, &self->model, &self->root);
        clNormal3D_SetFlags(self, 0x40000000, 0);
    } else {
        self->root = HSD_JObjLoadDesc(self->selected->descriptor);
    }
    self->count = clNormal3D_CountJObjs(self, self->root, 0);
    self->table = (JObj**)FUN_8003b120(self->count * 4);
    flattened = clNormal3D_FlattenJObjTree(self->root, self->table, 0);
    if (flattened != self->count) {
        DebugPrintf(lbl_802E97D0);
        for (;;) {}
    }
    if (FirstAnimation(self->selected->jointAnims) != 0 ||
        FirstAnimation(self->selected->materialAnims) != 0 ||
        FirstAnimation(self->selected->shapeAnims) != 0) {
        self->hasAnimations = 1;
    }
    return 1;
}
