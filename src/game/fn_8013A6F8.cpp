/*
 * 0x8013A6F8..0x8013A778: coin system shutdown.
 */
#pragma cplusplus on

struct ModelPair {
    void **vt;
    void *a;
    void *b;
};

/* TOP-END */

extern "C" {
void MemoryManager_Free(void *p);
void Object_DtorWithGXSync(void *o, int flag);
extern void *lbl_806D1528;
extern void *lbl_806D152C;
extern void *lbl_806D1530;
extern void *lbl_806D1534;
extern int lbl_806D1538;
void fn_8013A6F8(void);

#pragma section R ".extab_user"

#pragma section R ".extabindex_user"

}


extern "C" void fn_8013A6F8(void)
{
    if (lbl_806D1528) Object_DtorWithGXSync(lbl_806D1528, 1);
    if (lbl_806D152C) Object_DtorWithGXSync(lbl_806D152C, 1);
    if (lbl_806D1530) Object_DtorWithGXSync(lbl_806D1530, 1);
    if (lbl_806D1534) MemoryManager_Free(lbl_806D1534);
    lbl_806D1528 = 0;
    lbl_806D152C = 0;
    lbl_806D1530 = 0;
    lbl_806D1534 = 0;
    lbl_806D1538 = 0;
}

