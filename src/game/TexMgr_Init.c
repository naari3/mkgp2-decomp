/* TexMgr_Init
 *
 * 0x801F93F8 (size 0x84). Initializes a texture-manager state struct of at
 * least 0x230 bytes:
 *   - 6 leading floats (3 zeros, 2 ones, 1 zero)
 *   - 3 ints (0, 0, -1)
 *   - 512-byte 0xFF fill (memset)
 *   - tail (float 0.0, int 0, float 0.0)
 *
 * Singleton SDA2 constants lbl_806DA76C (= 0.0f) and lbl_806DA770 (= 1.0f)
 * are shared sda21 floats.
 *
 * Has extab/extabindex entry (extab @ 0x800176C0, extabindex @ 0x800290A8);
 * #pragma exceptions on lets CW auto-emit the singleton entries to keep
 * layout aligned with target.
 */

extern void *memset(void *dst, int c, unsigned int n);

extern const float lbl_806DA76C;  /* = 0.0f */
extern const float lbl_806DA770;  /* = 1.0f */

#pragma exceptions on
void TexMgr_Init(void *self) {
    float *fp = (float *)self;
    int *ip = (int *)self;

    fp[0] = lbl_806DA76C;
    fp[1] = lbl_806DA76C;
    fp[2] = lbl_806DA76C;
    fp[3] = lbl_806DA770;
    fp[4] = lbl_806DA770;
    ip[6] = 0;
    fp[5] = lbl_806DA76C;
    ip[7] = 0;
    ip[8] = -1;
    memset((char *)self + 0x24, 0xFFFF, 0x200);
    fp[0x89] = lbl_806DA76C;
    ip[0x8A] = 0;
    fp[0x8B] = lbl_806DA76C;
}
#pragma exceptions reset
