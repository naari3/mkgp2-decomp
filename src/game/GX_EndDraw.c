/*
 * GX_EndDraw @ 0x801F7C18 (size 0xC0).
 *
 * Sibling of GX_BeginDraw (extab_group=None but eg=1: own extab/extabindex
 * entry, emitted via #pragma exceptions on / reset).
 *
 * Takes a single uint mode. Writes the low byte to a sbss flag, runs a
 * teardown helper, then dispatches DbgGx_Xfreg100A_Set3 with two distinct
 * argument triples depending on whether mode is zero. The mode != 0 case is
 * the if-branch in source so CW lays it out before the zero branch with a
 * forward `beq` (matches target). Final block sequentially writes 5 and 0 to
 * two adjacent sdata words.
 *
 * lbl_806D1968 (sbss, 1 byte): mode flag.
 * lbl_806D196C (sbss, 0xC = three 4-byte slots): [0]=5, [1]=0 at exit.
 * lbl_806796FC (bss, 0x4C): shared with GX_BeginDraw, loaded via ha/lo pair.
 *
 * Compiled with extra_cflags=["-sdata 16"] so the 12-byte lbl_806D196C is
 * treated as SDA-resident (default threshold is 8); target asm uses the
 * single-instruction `addi r3, r13, lbl@sda21` form, which CW only emits when
 * the symbol fits inside the configured sdata threshold.
 */

extern void DbgGx_Xfreg100B_Set1(int);
extern void DbgGx_Xfreg100A_Set3(int, int, int);
extern void fn_801F6804(void *);
extern void fn_801F6588(unsigned int);
extern void fn_8026951C(int, int, int, int, int);
extern void DbgGx_GenModeTail7(int, int, int, int, int, int, int);

extern unsigned char lbl_806D1968;
extern int lbl_806D196C[3];
extern char lbl_806796FC[];

#pragma exceptions on
void GX_EndDraw(unsigned int mode) {
    lbl_806D1968 = (unsigned char)mode;
    DbgGx_Xfreg100B_Set1(0);
    if (mode & 0xFF) {
        DbgGx_Xfreg100A_Set3(1, 3, 1);
    } else {
        DbgGx_Xfreg100A_Set3(0, 7, 1);
    }
    fn_801F6804(&lbl_806796FC);
    fn_801F6588(mode);
    fn_8026951C(4, 0, 1, 4, 0);
    DbgGx_GenModeTail7(4, 0, 1, 1, 0, 0, 2);
    lbl_806D196C[0] = 5;
    lbl_806D196C[1] = 0;
}
#pragma exceptions reset
