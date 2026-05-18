/* SuikaBallObj_Render
 *
 * 0x801240B4 (size 0x30). Conditional tail-call wrapper around
 * Object_RenderJObjTree (fn_80034260). Dereferences param_1 to get a JObj
 * pointer; if non-null, calls Object_RenderJObjTree(jobj, 7) and returns its
 * result. Otherwise returns 0 (the loaded null naturally lives in r3).
 *
 * Has extab/extabindex entry with the "Large Frame: Yes" flag, so emit via
 * #pragma exceptions on / reset.
 */

extern int fn_80034260(void *jobj, int flag);

#pragma exceptions on
int SuikaBallObj_Render(void **param_1) {
    void *jobj = *param_1;
    if (jobj != 0) {
        return fn_80034260(jobj, 7);
    }
    return (int)jobj;
}
#pragma exceptions reset
