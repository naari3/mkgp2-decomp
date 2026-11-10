#include "tobj.h"

GXTexCoordID HSD_TObjSetupTextureCoordGen_data_806D0C90 = GX_TEXCOORD_NULL;
char lbl_806D0C94[7] = "tobj.c";
char lbl_806D0C9C[5] = "tobj";
char lbl_806D0CA4[5] = "cobj";
char lbl_806D0CAC[2] = "0";
char lbl_806D0CB0[5] = "tlut";
#pragma explicit_zero_data on
void* HSD_Index2TexMtx_data_806D0CB8 = 0;
#pragma explicit_zero_data reset
char lbl_806D0CBC[4] = "new";
char lbl_806D0CC0[4] = "tev";
char lbl_806D0CC4[6] = "idesc";
Mtx HSD_TObjSetupTextureCoordGen_bss_806CCF80;
const float lbl_806DCB8C = 1.0F;
const float lbl_806DCB90 = 255.0F;
const float lbl_806DCB94 = 1.00000001335e-10F;
/* 0x806DCB98 / 0x806DCBB0 are doubles, but this pool starts at 4 mod 8
 * and the target packs them without padding: emit them as word pairs. */
const unsigned int lbl_806DCB98[2] = {0x43300000, 0};
const float lbl_806DCBA0 = 0.5F;
const float lbl_806DCBA4 = -0.5F;
const unsigned int lbl_806DCBA8[2] = {0xBF800000, 0}; /* -1.0f + the pad before the next double */
const unsigned int lbl_806DCBB0[2] = {0xBFE00000, 0};
