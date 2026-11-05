typedef struct ObjViewEntry {
    void *vt;
    void *object;
    float value;
} ObjViewEntry;

extern char lbl_80490FE0[];
extern char lbl_80495E8C[];
extern const float lbl_806D9438;

ObjViewEntry *fn_8018E510(ObjViewEntry *self, void *object) {
    self->vt = lbl_80490FE0;
    self->vt = lbl_80495E8C;
    self->object = object;
    self->value = lbl_806D9438;
    return self;
}
