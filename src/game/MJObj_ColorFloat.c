/* Set an MJObj's RGBA colour from float channels (0.0 .. 1.0). */
typedef struct MJObj MJObj;

extern unsigned int g_mjobjClassInfo[]; /* MJObj class info */
extern int hsdObjIsDescendantOf(void *obj, void *info);
extern void MJObj_SetColorRGBA(MJObj *self, unsigned char r, unsigned char g,
                               unsigned char b, unsigned char a);

#pragma exceptions on
#pragma use_lmw_stmw on
void MJObj_SetColorRGBA_Float(MJObj *self, float r, float g, float b, float a)
{
    int ir = 0.5f * (255.0f * r);
    int ig = 0.5f * (255.0f * g);
    int ib = 0.5f * (255.0f * b);
    int ia;

    a = (a > 1.0f) ? 1.0f : a;
    a = (a < 0.0f) ? 0.0f : a;
    ia = 255.0f * a;

    if (hsdObjIsDescendantOf(self, g_mjobjClassInfo)) {
        MJObj_SetColorRGBA(self, ir, ig, ib, ia);
    }
}
#pragma use_lmw_stmw reset
#pragma exceptions reset
