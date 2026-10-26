/* Render the Jyugemu flag model once it is visible. */
typedef struct JyugemuFlag {
    void *model;   /* 0x00 */
    unsigned char pad04[0x4];
    void *visible; /* 0x08 */
} JyugemuFlag;

extern void Object_RenderJObjTree(void *model, int mask);

int Jyugemu_Flag_Render(JyugemuFlag *self)
{
    if (self->model == 0) {
        return 0;
    }
    if (self->visible == 0) {
        return 0;
    }
    Object_RenderJObjTree(self->model, 7);
    return 1;
}
