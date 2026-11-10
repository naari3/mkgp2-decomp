#include "musyx/musyx.h"

#include "musyx/assert.h"
#include "musyx/sal.h"
/* --- owned .data 0x804FB040..0x804FB840 (tools/own_data.py) --- */
#pragma force_active on
float chorus_fx_data_804FB040[512] = { 0.0975036621f, 0.802215576f, 0.101593018f, -0.0009765625f, 0.0935058594f, 0.802032471f, 0.105804443f, -0.00103759766f, 0.0895996094f, 0.801696777f, 0.110107422f, -0.00115966797f, 0.0857849121f, 0.801177979f, 0.114471436f, -0.00128173828f, 0.08203125f, 0.800476074f, 0.118927002f, -0.00140380859f, 0.0783691406f, 0.799621582f, 0.123474121f, -0.00152587891f, 0.074798584f, 0.798614502f, 0.128143311f, -0.00164794922f, 0.0713500977f, 0.797424316f, 0.132873535f, -0.00177001953f, 0.0679626465f, 0.796051025f, 0.137695312f, -0.00192260742f, 0.0646972656f, 0.794525146f, 0.142608643f, -0.00204467773f, 0.0614929199f, 0.79284668f, 0.147613525f, -0.00219726562f, 0.0583496094f, 0.790985107f, 0.152709961f, -0.00231933594f, 0.0553283691f, 0.78894043f, 0.157897949f, -0.00247192383f, 0.0523681641f, 0.786743164f, 0.16317749f, -0.0026550293f, 0.0494995117f, 0.784423828f, 0.168518066f, -0.00280761719f, 0.0467224121f, 0.781890869f, 0.173980713f, -0.00299072266f, 0.0440063477f, 0.779205322f, 0.179504395f, -0.00314331055f, 0.0414123535f, 0.776367188f, 0.185119629f, -0.00332641602f, 0.0388793945f, 0.773376465f, 0.190826416f, -0.00350952148f, 0.0364074707f, 0.770233154f, 0.196594238f, -0.00369262695f, 0.0340270996f, 0.766937256f, 0.202484131f, -0.00387573242f, 0.0317382812f, 0.76348877f, 0.208435059f, -0.00405883789f, 0.029510498f, 0.759857178f, 0.214447021f, -0.00427246094f, 0.0273742676f, 0.756103516f, 0.220550537f, -0.00445556641f, 0.0252990723f, 0.752197266f, 0.226745605f, -0.00466918945f, 0.0233154297f, 0.748168945f, 0.233001709f, -0.00485229492f, 0.0213928223f, 0.743988037f, 0.239318848f, -0.00506591797f, 0.0195617676f, 0.739654541f, 0.245727539f, -0.00531005859f, 0.017791748f, 0.735198975f, 0.252197266f, -0.00552368164f, 0.0160522461f, 0.73059082f, 0.258728027f, -0.00570678711f, 0.0144042969f, 0.725860596f, 0.265350342f, -0.00592041016f, 0.0128173828f, 0.721008301f, 0.272033691f, -0.00616455078f, 0.0113220215f, 0.716003418f, 0.278778076f, -0.00637817383f, 0.00988769531f, 0.710906982f, 0.285583496f, -0.0065612793f, 0.0085144043f, 0.705657959f, 0.292449951f, -0.00677490234f, 0.00720214844f, 0.700317383f, 0.299346924f, -0.00701904297f, 0.00592041016f, 0.694854736f, 0.306335449f, -0.00723266602f, 0.00469970703f, 0.68927002f, 0.31338501f, -0.00741577148f, 0.00357055664f, 0.683563232f, 0.320465088f, -0.00762939453f, 0.00247192383f, 0.677734375f, 0.327606201f, -0.00787353516f, 0.00143432617f, 0.671844482f, 0.334777832f, -0.0080871582f, 0.000457763672f, 0.66583252f, 0.34197998f, -0.00827026367f, -0.00048828125f, 0.659729004f, 0.349243164f, -0.00845336914f, -0.00134277344f, 0.653533936f, 0.356567383f, -0.00863647461f, -0.00216674805f, 0.647216797f, 0.363891602f, -0.00885009766f, -0.00296020508f, 0.640838623f, 0.371276855f, -0.00903320312f, -0.00369262695f, 0.634338379f, 0.378692627f, -0.00921630859f, -0.00436401367f, 0.6277771f, 0.386138916f, -0.00933837891f, -0.00497436523f, 0.621154785f, 0.393615723f, -0.0094909668f, -0.0055847168f, 0.614440918f, 0.401092529f, -0.00964355469f, -0.0061340332f, 0.607635498f, 0.408599854f, -0.00979614258f, -0.00665283203f, 0.600769043f, 0.416107178f, -0.00991821289f, -0.00714111328f, 0.593841553f, 0.42364502f, -0.0100097656f, -0.00756835938f, 0.586853027f, 0.431213379f, -0.0101318359f, -0.00796508789f, 0.579772949f, 0.438751221f, -0.0102233887f, -0.00833129883f, 0.572662354f, 0.44631958f, -0.0102844238f, -0.00866699219f, 0.56552124f, 0.453887939f, -0.010345459f, -0.00897216797f, 0.558319092f, 0.461456299f, -0.0104064941f, -0.00921630859f, 0.551055908f, 0.469024658f, -0.0104064941f, -0.00946044922f, 0.543731689f, 0.476593018f, -0.0104064941f, -0.00967407227f, 0.536407471f, 0.484130859f, -0.0103759766f, -0.00985717773f, 0.529022217f, 0.491668701f, -0.0103759766f, -0.0100097656f, 0.521606445f, 0.499176025f, -0.0103149414f, -0.0101318359f, 0.514160156f, 0.50668335f, -0.0102539062f, -0.0102539062f, 0.50668335f, 0.514160156f, -0.0101318359f, -0.0103149414f, 0.499176025f, 0.521606445f, -0.0100097656f, -0.0103759766f, 0.491668701f, 0.529022217f, -0.00985717773f, -0.0103759766f, 0.484130859f, 0.536407471f, -0.00967407227f, -0.0104064941f, 0.476593018f, 0.543731689f, -0.00946044922f, -0.0104064941f, 0.469024658f, 0.551055908f, -0.00921630859f, -0.0104064941f, 0.461456299f, 0.558319092f, -0.00897216797f, -0.010345459f, 0.453887939f, 0.56552124f, -0.00866699219f, -0.0102844238f, 0.44631958f, 0.572662354f, -0.00833129883f, -0.0102233887f, 0.438751221f, 0.579772949f, -0.00796508789f, -0.0101318359f, 0.431213379f, 0.586853027f, -0.00756835938f, -0.0100097656f, 0.42364502f, 0.593841553f, -0.00714111328f, -0.00991821289f, 0.416107178f, 0.600769043f, -0.00665283203f, -0.00979614258f, 0.408599854f, 0.607635498f, -0.0061340332f, -0.00964355469f, 0.401092529f, 0.614440918f, -0.0055847168f, -0.0094909668f, 0.393615723f, 0.621154785f, -0.00497436523f, -0.00933837891f, 0.386138916f, 0.6277771f, -0.00436401367f, -0.00921630859f, 0.378692627f, 0.634338379f, -0.00369262695f, -0.00903320312f, 0.371276855f, 0.640838623f, -0.00296020508f, -0.00885009766f, 0.363891602f, 0.647216797f, -0.00216674805f, -0.00863647461f, 0.356567383f, 0.653533936f, -0.00134277344f, -0.00845336914f, 0.349243164f, 0.659729004f, -0.00048828125f, -0.00827026367f, 0.34197998f, 0.66583252f, 0.000457763672f, -0.0080871582f, 0.334777832f, 0.671844482f, 0.00143432617f, -0.00787353516f, 0.327606201f, 0.677734375f, 0.00247192383f, -0.00762939453f, 0.320465088f, 0.683563232f, 0.00357055664f, -0.00741577148f, 0.31338501f, 0.68927002f, 0.00469970703f, -0.00723266602f, 0.306335449f, 0.694854736f, 0.00592041016f, -0.00701904297f, 0.299346924f, 0.700317383f, 0.00720214844f, -0.00677490234f, 0.292449951f, 0.705657959f, 0.0085144043f, -0.0065612793f, 0.285583496f, 0.710906982f, 0.00988769531f, -0.00637817383f, 0.278778076f, 0.716003418f, 0.0113220215f, -0.00616455078f, 0.272033691f, 0.721008301f, 0.0128173828f, -0.00592041016f, 0.265350342f, 0.725860596f, 0.0144042969f, -0.00570678711f, 0.258728027f, 0.73059082f, 0.0160522461f, -0.00552368164f, 0.252197266f, 0.735198975f, 0.017791748f, -0.00531005859f, 0.245727539f, 0.739654541f, 0.0195617676f, -0.00506591797f, 0.239318848f, 0.743988037f, 0.0213928223f, -0.00485229492f, 0.233001709f, 0.748168945f, 0.0233154297f, -0.00466918945f, 0.226745605f, 0.752197266f, 0.0252990723f, -0.00445556641f, 0.220550537f, 0.756103516f, 0.0273742676f, -0.00427246094f, 0.214447021f, 0.759857178f, 0.029510498f, -0.00405883789f, 0.208435059f, 0.76348877f, 0.0317382812f, -0.00387573242f, 0.202484131f, 0.766937256f, 0.0340270996f, -0.00369262695f, 0.196594238f, 0.770233154f, 0.0364074707f, -0.00350952148f, 0.190826416f, 0.773376465f, 0.0388793945f, -0.00332641602f, 0.185119629f, 0.776367188f, 0.0414123535f, -0.00314331055f, 0.179504395f, 0.779205322f, 0.0440063477f, -0.00299072266f, 0.173980713f, 0.781890869f, 0.0467224121f, -0.00280761719f, 0.168518066f, 0.784423828f, 0.0494995117f, -0.0026550293f, 0.16317749f, 0.786743164f, 0.0523681641f, -0.00247192383f, 0.157897949f, 0.78894043f, 0.0553283691f, -0.00231933594f, 0.152709961f, 0.790985107f, 0.0583496094f, -0.00219726562f, 0.147613525f, 0.79284668f, 0.0614929199f, -0.00204467773f, 0.142608643f, 0.794525146f, 0.0646972656f, -0.00192260742f, 0.137695312f, 0.796051025f, 0.0679626465f, -0.00177001953f, 0.132873535f, 0.797424316f, 0.0713500977f, -0.00164794922f, 0.128143311f, 0.798614502f, 0.074798584f, -0.00152587891f, 0.123474121f, 0.799621582f, 0.0783691406f, -0.00140380859f, 0.118927002f, 0.800476074f, 0.08203125f, -0.00128173828f, 0.114471436f, 0.801177979f, 0.0857849121f, -0.00115966797f, 0.110107422f, 0.801696777f, 0.0895996094f, -0.00103759766f, 0.105804443f, 0.802032471f, 0.0935058594f, -0.0009765625f, 0.101593018f, 0.802215576f, 0.0975036621f };
#pragma force_active reset

/* File-local data is not split into this unit yet: refer to it by address. */
#define rsmpTab12khz chorus_fx_data_804FB040
extern float rsmpTab12khz[512];

extern const double i2fMagic;

#ifdef __MWERKS__
// clang-format off
static asm void do_src1(_SND_CHORUS_SRCINFO* src) {
  nofralloc  

  stwu r1, -0x40(sp)
  stmw r26, 0x28(sp)

  
  lwz r4, 0xc(r3)
  lwz r5, 0x10(r3)

  lwz r6, 0x14(r3)

  lwz r8, 0x1c(r3)
  lwz r7, 0x20(r3)

  lwz r31, 4(r3)
  
  lwz r30, 0(r3)
  
  lwz r9, 8(r3)
  
  lis r10, 0x4330
  stw r10, 8(sp)
  stw r10, 0x10(sp)
  stw r10, 0x18(sp)
  stw r10, 0x20(sp)
  
  lis r10, i2fMagic@ha
  lfd f9, i2fMagic@l(r10)
  
  slwi r10, r5, 2
  lwz r11, 0(r9)
  
  lwz r29, 4(r9)
  lwz r28, 8(r9)  
  lwzx r27, r31, r10

  xoris r11, r11, 0x8000
  xoris r29, r29, 0x8000  
  stw r11, 0xc(sp)
  xoris r28, r28, 0x8000
  stw r29, 0x14(sp)
  xoris r27, r27, 0x8000
  stw r28, 0x1c(sp)
  lfd f1, 8(sp)
  stw r27, 0x24(sp)
  lfd f2, 0x10(sp)  
  fsubs f1, f1, f9
  lfd f3, 0x18(sp)
  fsubs f2, f2, f9
  lfd f4, 0x20(sp)
  fsubs f3, f3, f9
  fsubs f4, f4, f9
  
  li r26, -4
  
  lis r12, rsmpTab12khz@ha
  addi r12, r12, rsmpTab12khz@l
  
  li r9, 0xa0
  mtctr r9
lbl_803B6D5C:
  rlwinm r10, r4, 7, 0x15, 0x1b

  addc r4, r4, r6

  add r10, r10, r12
  
  mcrxr cr0

  lfs f5, 0(r10)

  beq lbl_803B6DA4

  lfs f6, 4(r10)

  fmuls f10, f1, f5

  lfs f7, 8(r10)
  
  fmadds f10, f2, f6, f10
  
  lfs f8, 0xc(r10)

  fmadds f10, f3, f7, f10

  addi r30, r30, 4

  fmadds f10, f4, f8, f10

  fctiwz f10, f10

  stfiwx f10, r26, r30

  bdnz lbl_803B6D5C
  
  b lbl_803B6E10


lbl_803B6DA4:
  addi r5, r5, 1

  lfs f6, 4(r10)
  
  fmuls f10, f1, f5
  
  cmpw r5, r8
  
  fmr f1, f2
  
  lfs f7, 8(r10)
  
  fmadds f10, f2, f6, f10
  
  fmr f2, f3
  
  lfs f8, 0xc(r10)
  
  fmadds f10, f3, f7, f10
  
  addi r30, r30, 4
  
  fmr f3, f4
  
  bne+ lbl_803B6DDC
  mr r5, r7
  
lbl_803B6DDC:
  fmadds f10, f4, f8, f10

  slwi r9, r5, 2

  bdz lbl_803B6E08

  lwzx r10, r9, r31
  
  fctiwz f10, f10
  
  xoris r10, r10, 0x8000
  
  stw r10, 0xc(sp)
  
  stfiwx f10, r26, r30
  
  lfd f4, 8(sp)
  
  fsubs f4, f4, f9
  
  b lbl_803B6D5C


lbl_803B6E08:
  fctiwz f10, f10
  stfiwx f10, r26, r30


lbl_803B6E10:
  lwz r9, 8(r3)
  
  fctiwz f1, f1
  fctiwz f2, f2
  fctiwz f3, f3
  
  stfiwx f1, r0, r9
  addi r10, r9, 4
  stfiwx f2, r0, r10
  addi r10, r9, 8
  stfiwx f3, r0, r10
  
  stw r4, 0xc(r3)
  stw r5, 0x10(r3)
  
  lmw r26, 0x28(sp)
  addi r1, r1, 0x40
  blr
}
/* clang-format on */
#else
static void do_src1(_SND_CHORUS_SRCINFO *src) {
  float s0 = (float)src->old[0];
  float s1 = (float)src->old[1];
  float s2 = (float)src->old[2];
  float s3 = (float)src->smpBase[src->posHi];

  for (u32 i = 0; i < 160; ++i) {
    const float *coef = &rsmpTab12khz[((src->posLo >> 9) & 0x7f) * 4];
    src->dest[i] = (s32)(s0 * coef[0] + s1 * coef[1] + s2 * coef[2] + s3 * coef[3]);

    u32 oldPosLo = src->posLo;
    src->posLo += src->pitchLo;
    if (src->posLo < oldPosLo) {
      src->posHi += 1;
      if (src->posHi == src->trigger)
        src->posHi = src->target;

      s0 = s1;
      s1 = s2;
      s2 = s3;
      s3 = (float)src->smpBase[src->posHi];
    }
  }

  src->old[0] = (s32)s0;
  src->old[1] = (s32)s1;
  src->old[2] = (s32)s2;
}
#endif

#ifdef __MWERKS__
/* clang-format off */
static asm void do_src2(register _SND_CHORUS_SRCINFO* src) {
#define posLoV r4
#define posHiV r5
#define pitchLoV r6
#define triggerV r8
#define targetV r7
#define oldPtr r9
#define destPtr r30
#define smpBasePtr r31

  nofralloc;
  /* Save stack state to stack */
  stwu r1, -0x40(sp);
  stmw r26, 0x28(sp);

  lwz posLoV, src->posLo;
  lwz posHiV, src->posHi;

  lwz pitchLoV, src->pitchLo;

  lwz triggerV, src->trigger;
  lwz targetV, src->target;

  lwz smpBasePtr, src->smpBase;

  lwz destPtr, src->dest;

  lwz oldPtr, src->old;
  /* Store upper portion of int->float conversion constant */
  lis r10, 0x4330;
  stw r10, 0x08(sp);
  stw r10, 0x10(sp);
  stw r10, 0x18(sp);
  stw r10, 0x20(sp);

  lis r10, i2fMagic @ha;
  lfd f9, i2fMagic @l(r10);

  // posHi * 4
  slwi r10, posHiV, 2;
  lwz r11, 0(oldPtr);
  lwz r29, 4(oldPtr);
  lwz r28, 8(oldPtr);
  lwzx r27, smpBasePtr, r10;

  xoris r11, r11, 0x8000;
  xoris r29, r29, 0x8000;
  stw r11, 0xc(sp);
  xoris r28, r28, 0x8000;
  stw r29, 0x14(sp);
  xoris r27, r27, 0x8000;
  stw r28, 0x1c(sp);
  lfd f1, 0x08(sp);
  stw r27, 0x24(sp);
  lfd f2, 0x10(sp);
  fsubs f1, f1, f9;
  lfd f3, 0x18(sp);
  fsubs f2, f2, f9;
  lfd f4, 0x20(sp);
  fsubs f3, f3, f9;
  fsubs f4, f4, f9;
  /* Some offset? */
  li r26, -4;

  lis r12, rsmpTab12khz @ha;
  addi r12, r12, rsmpTab12khz @l;

  li r9, 0xa0;
  mtctr r9;
lbl_803B6EF4:
  rlwinm r10, posLoV, 7, 0x15, 0x1b;

  addc posLoV, posLoV, pitchLoV;

  add r10, r10, r12;

  mcrxr cr0;

  addi posHiV, posHiV, 1;

  lfs f5, 0(r10);

  beq lbl_803B6F70;

  lfs f6, 4(r10);

  fmuls f10, f1, f5;

  cmpw posHiV, triggerV;

  fmr f1, f2;

  lfs f7, 8(r10);

  fmadds f10, f2, f6, f10;

  fmr f2, f3;

  lfs f8, 0xc(r10);

  fmadds f10, f3, f7, f10;

  addi destPtr, destPtr, 4;

  fmr f3, f4;

  bne + lbl_803B6F44;
  mr posHiV, targetV;

lbl_803B6F44:
  fmadds f10, f4, f8, f10;

  slwi r9, posHiV, 2;

  bdz lbl_803B6FF4;

  lwzx r10, r9, smpBasePtr;

  fctiwz f10, f10;

  xoris r10, r10, 0x8000;

  stw r10, 0xc(sp);

  stfiwx f10, r26, destPtr;

  lfd f4, 8(sp);

  fsubs f4, f4, f9;

  b lbl_803B6EF4;

lbl_803B6F70:

  cmpw posHiV, triggerV;

  lfs f6, 4(r10);

  bne + lbl_803B6F80;
  mr posHiV, targetV;

lbl_803B6F80:

  slwi r11, posHiV, 2;
  addi posHiV, posHiV, 1;

  lwzx r29, r11, smpBasePtr;

  fmuls f10, f1, f5;

  cmpw posHiV, triggerV;
  xoris r29, r29, 0x8000;

  fmr f1, f3;

  lfs f7, 8(r10);

  stw r29, 0xc(sp);

  fmadds f10, f2, f6, f10;

  lfs f8, 0xc(r10);

  fmadds f10, f3, f7, f10;

  lfd f3, 8(sp);

  fmr f2, f4;

  addi destPtr, destPtr, 4;

  fsubs f3, f3, f9;

  bne + lbl_803B6FC8;
  mr posHiV, targetV;

lbl_803B6FC8:

  fmadds f10, f4, f8, f10;

  slwi r9, posHiV, 2;

  bdz lbl_803B6FF4;

  lwzx r10, r9, smpBasePtr;

  fctiwz f10, f10;

  xoris r10, r10, 0x8000;

  stw r10, 0xc(sp);

  stfiwx f10, r26, destPtr;
  lfd f4, 8(sp);
  fsubs f4, f4, f9;

  b lbl_803B6EF4;

lbl_803B6FF4:

  fctiwz f10, f10;
  stfiwx f10, r26, destPtr;

  lwz r9, 8(r3);

  fctiwz f1, f1;
  fctiwz f2, f2;
  fctiwz f3, f3;
  stfiwx f1, r0, r9;
  addi r10, r9, 4;
  stfiwx f2, r0, r10;
  addi r10, r9, 8;
  stfiwx f3, r0, r10;

  stw posLoV, src->posLo;
  stw posHiV, src->posHi;

  /* Pop and restore LR to original values */
  lmw r26, 0x28(sp);
  addi r1, r1, 0x40;
  blr;

#undef posLoV
#undef posHiV
#undef pitchLoV
#undef triggerV
#undef targetV
#undef oldPtr
#undef destPtr
#undef smpBasePtr
}
#else
static void do_src2(register _SND_CHORUS_SRCINFO* src) {
  float s0 = (float)src->old[0];
  float s1 = (float)src->old[1];
  float s2 = (float)src->old[2];
  float s3 = (float)src->smpBase[src->posHi];

  for (u32 i = 0; i < 160; ++i) {
    const float* coef = &rsmpTab12khz[((src->posLo >> 9) & 0x7f) * 4];
    src->dest[i] = (s32)(s0 * coef[0] + s1 * coef[1] + s2 * coef[2] + s3 * coef[3]);

    u32 oldPosLo = src->posLo;
    src->posLo += src->pitchLo;
    src->posHi += 1;

    if (src->posLo < oldPosLo) {
      if (src->posHi == src->trigger)
        src->posHi = src->target;
      float next0 = (float)src->smpBase[src->posHi];
      src->posHi += 1;
      if (src->posHi == src->trigger)
        src->posHi = src->target;

      s0 = s2;
      s1 = s3;
      s2 = next0;
      s3 = (float)src->smpBase[src->posHi];
    } else {
      if (src->posHi == src->trigger)
        src->posHi = src->target;

      s0 = s1;
      s1 = s2;
      s2 = s3;
      s3 = (float)src->smpBase[src->posHi];
    }
  }

  src->old[0] = (s32)s0;
  src->old[1] = (s32)s1;
  src->old[2] = (s32)s2;
}
#endif

void sndAuxCallbackChorus(u8 reason, SND_AUX_INFO* info, void* user) {
  SND_AUX_CHORUS* c;
  s32 *leftD, *rightD, *surD, *leftS, *rightS, *surS;
  u32 i;
  u8 nextCurrentLast;
  switch (reason) {
  case SND_AUX_REASON_BUFFERUPDATE:
    c = (SND_AUX_CHORUS*)user;
    nextCurrentLast = (c->work.currentLast + 1) % 3;
    leftD = c->work.lastLeft[nextCurrentLast];
    rightD = c->work.lastRight[nextCurrentLast];
    surD = c->work.lastSur[nextCurrentLast];
    leftS = info->data.bufferUpdate.left;
    rightS = info->data.bufferUpdate.right;
    surS = info->data.bufferUpdate.surround;

    for (i = 0; i < 160; ++i) {
      *leftD++ = *leftS++;
      *rightD++ = *rightS++;
      *surD++ = *surS++;
    }

    c->work.src.pitchHi = (c->work.pitchOffset >> 0x10) + 1;
#if MUSY_TARGET == MUSY_TARGET_PC
    c->work.src.pitchLo = (u32)c->work.pitchOffset << 16;
#else
    c->work.src.pitchLo = ((c->work.pitchOffset & 0xFFFF) << 16);
#endif
    if (--c->work.pitchOffsetPeriodCount == 0) {
      c->work.pitchOffsetPeriodCount = c->work.pitchOffsetPeriod;
      c->work.pitchOffset = -c->work.pitchOffset;
    }

    for (i = 0; i < 3; ++i) {
      c->work.src.posHi = c->work.currentPosHi;
      c->work.src.posLo = c->work.currentPosLo;
      switch (i) {
      case 0:
        c->work.src.smpBase = c->work.lastLeft[0];
        c->work.src.dest = info->data.bufferUpdate.left;
        c->work.src.old = c->work.oldLeft;
        break;
      case 1:
        c->work.src.smpBase = c->work.lastRight[0];
        c->work.src.dest = info->data.bufferUpdate.right;
        c->work.src.old = c->work.oldRight;
        break;
      case 2:
        c->work.src.smpBase = c->work.lastSur[0];
        c->work.src.dest = info->data.bufferUpdate.surround;
        c->work.src.old = c->work.oldSur;
        break;
      }

      switch (c->work.src.pitchHi) {
      case 0:
        do_src1(&c->work.src);
        break;
      case 1:
        do_src2(&c->work.src);
        break;
      }
    }

    c->work.currentPosHi = c->work.src.posHi % 480;
    c->work.currentPosLo = c->work.src.posLo;
    c->work.currentLast = nextCurrentLast;
    break;
  case SND_AUX_REASON_PARAMETERUPDATE:
    break;
  default:
  #line 957
    MUSY_ASSERT(FALSE);
    break;
  }
}

bool sndAuxCallbackUpdateSettingsChorus(SND_AUX_CHORUS* ch) {
  ch->work.currentPosHi = 0x140 - ((ch->baseDelay - 5) << 5);
  ch->work.currentPosLo = 0;
  ch->work.currentPosHi = (ch->work.currentPosHi + (ch->work.currentLast - 1) * 0xa0) % 0x1e0;
  ch->work.pitchOffsetPeriod = ((ch->period / 5) + 1) & ~1;
  ch->work.pitchOffsetPeriodCount = (u32)ch->work.pitchOffsetPeriod >> 1;
  ch->work.pitchOffset = (ch->variation << 16) / (ch->work.pitchOffsetPeriod * 5);
  return TRUE;
}

bool sndAuxCallbackPrepareChorus(SND_AUX_CHORUS* chorus) {
  u32 i;
  s32* lastLeft;
  s32* lastRight;
  s32* lastSur;

  chorus->work.lastLeft[0] = (s32*)salMalloc(0x1680);

  if (chorus->work.lastLeft[0] != NULL) {
    chorus->work.lastRight[0] = chorus->work.lastLeft[0] + 0x1e0;
    chorus->work.lastSur[0] = chorus->work.lastRight[0] + 0x1e0;

    for (i = 1; i < 3; ++i) {
      chorus->work.lastLeft[i] = chorus->work.lastLeft[0] + i * 0xa0;
      chorus->work.lastRight[i] = chorus->work.lastRight[0] + i * 0xa0;
      chorus->work.lastSur[i] = chorus->work.lastSur[0] + i * 0xa0;
    }

    lastLeft = chorus->work.lastLeft[0];
    lastRight = chorus->work.lastRight[0];
    lastSur = chorus->work.lastSur[0];
    for (i = 0; i < 0x140; i += 1) {
      *lastLeft++ = 0;
      *lastRight++ = 0;
      *lastSur++ = 0;
    }

    chorus->work.currentLast = 1;
    chorus->work.oldLeft[0] = chorus->work.oldLeft[1] = chorus->work.oldLeft[2] = chorus->work.oldLeft[3] = 0;
    chorus->work.oldRight[0] = chorus->work.oldRight[1] = chorus->work.oldRight[2] = chorus->work.oldRight[3] = 0;
    chorus->work.oldSur[0] = chorus->work.oldSur[1] = chorus->work.oldSur[2] = chorus->work.oldSur[3] = 0;
    chorus->work.src.trigger = 480;
    chorus->work.src.target = 0;
    return sndAuxCallbackUpdateSettingsChorus(chorus);
  }
  return FALSE;
}

bool sndAuxCallbackShutdownChorus(SND_AUX_CHORUS* ch) {
  salFree(ch->work.lastLeft[0]);
  return TRUE;
}
