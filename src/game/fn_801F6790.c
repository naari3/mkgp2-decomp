/* Restores a saved GX scissor/viewport/projection/cull state. */
typedef struct GXSavedState {
    unsigned char valid;
    int cullMode;
    float projection[7];
    float viewport[6];
    int scissor[4];
} GXSavedState;

void GXSetScissor(int x, int y, int w, int h);
void GXSetViewport(float x, float y, float w, float h, float nz, float fz);
void GXSetProjectionv(const float *p);
void GXSetCullMode(int mode);

void fn_801F6790(GXSavedState *s) {
    if (s->valid) {
        GXSetScissor(s->scissor[0], s->scissor[1], s->scissor[2], s->scissor[3]);
        GXSetViewport(s->viewport[0], s->viewport[1], s->viewport[2], s->viewport[3], s->viewport[4], s->viewport[5]);
        GXSetProjectionv(s->projection);
        GXSetCullMode(s->cullMode);
    }
}
