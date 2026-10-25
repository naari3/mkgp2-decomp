#include "musyx/musyx.h"
#include "musyx/platform.h"
#include "musyx/snd.h"
#include "musyx/synth.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* Data is not split into this unit yet: refer to it by address. */
#define i2fMagic lbl_806DCB08
#define sqrtConsts lbl_803F2A88
#define _sinConsts lbl_803F2A94
#define sndSintab lbl_804F8950
#define last_rnd lbl_806D0C58
extern const double i2fMagic;
extern const float sqrtConsts[3];
extern const float _sinConsts[8];
extern s16 sndSintab[1024];
extern u32 last_rnd;

#define SINTAB_ELEMENT_COUNT (sizeof(sndSintab) / sizeof(u16) - 1)

u16 sndRand(void) {
#if MUSY_TARGET == MUSY_TARGET_PC
  last_rnd *= 2822053219u;
#else
  last_rnd *= 2822053219;
#endif
  return last_rnd >> 6;
}

s16 sndSin(u16 angle) {
  angle &= 0xFFF;
  if (angle < 1024) {
    return sndSintab[angle];
  }
  if (angle < 2048) {
    return sndSintab[SINTAB_ELEMENT_COUNT - (angle & SINTAB_ELEMENT_COUNT)];
  }
  if (angle < 3072) {
    return (s16)-sndSintab[angle & SINTAB_ELEMENT_COUNT];
  }
  return -sndSintab[SINTAB_ELEMENT_COUNT - (angle & SINTAB_ELEMENT_COUNT)];
}

void *sndBSearch(void *key, void *base, s32 num, s32 len, SND_COMPARE cmp) {
  long l;    // r31
  long r;    // r30
  long m;    // r29
  long c;    // r28
  void *ptr; // r27

  if (num != 0) {
    l = 1;
    r = num;
    do {
      // This is kind of gross....
      if ((c = cmp(key, (ptr = (void *)((size_t)base + len * ((m = (l + r) >> 1) - 1))))) == 0) {
        return ptr;
      }

      if (c < 0) {
        r = m - 1;
      } else {
        l = m + 1;
      }
    } while (l <= r);
  }
  return NULL;
}

#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
#if MUSY_TARGET == MUSY_TARGET_DOLPHIN
#if __MWERKS__
asm float sndSqrt(register float x) {
  nofralloc;
  lis r3, sqrtConsts @ha;
  lfs f3, sqrtConsts[2] @l(r3);
  lfs f0, sqrtConsts[0] @l(r3);
  lfs f2, sqrtConsts[1] @l(r3);

  fcmpo cr0, x, f3;
  frsqrte f3, x;

  beqlr;

  fmul f4, f3, f3;
  fmul f3, f3, f2;
  fnmsub f4, x, f4, f0;
  fmul f3, f3, f4;
  fmul f4, f3, f3;
  fmul f3, f3, f2;
  fnmsub f4, x, f4, f0;
  fmul f3, f3, f4;
  fmul f4, f3, f3;
  fmul f3, f3, f2;
  fnmsub f4, x, f4, f0;
  fmul f3, f3, f4;
  fmul x, x, f3;
  blr
}

asm float sndCos(register float x) {
  nofralloc;

  stwu sp, -(sizeof(int) * 4)(sp);

  lis r3, _sinConsts @ha;
  li r4, sizeof(float) * 3;
  addi r3, r3, _sinConsts @l;

  psq_l f6, (sizeof(float) * 4)(r3), 0, 0;
  psq_l f12, (sizeof(float) * 6)(r3), 0, 0;

  lis r7, i2fMagic @ha;

  ps_sum0 x, x, x, f6;

  lfd f3, i2fMagic @l(r7);

  ps_merge10 f11, f6, f6;

  fcmpo cr1, x, f12;
  lis r6, 0x4330;

  psq_l f0, (sizeof(float) * 0)(r3), 0, 0;
  psq_l f2, (sizeof(float) * 2)(r3), 0, 0;

  fabs x, x;
  fmuls x, x, f6;
  stw r6, 8(sp);

  fctiwz f7, x;
  stfiwx f7, sp, r4;
  lwz r5, (sizeof(int) * 3)(sp);
  srwi r7, r5, 1;
  xoris r6, r5, 0x8000;
  xor r7, r7, r5;
  stw r6, (sizeof(int) * 3)(sp);
  andi.r7, r7, 1;

  lfd f7, (sizeof(int) * 2)(sp);
  mcrf cr5, cr0;

  fsubs f7, f7, f3;
  fsubs x, x, f7;

  andi.r5, r5, 1;

  ps_muls1 x, x, f6;
  beq skip_sub;
  fsubs x, x, f11;
skip_sub:
  fmuls f4, x, x;

  beq cr5, skip_neg;
  ps_neg x, x;
skip_neg:
  fmuls f5, f4, f4;

  ps_muls0 f8, f0, x;
  ps_muls0 f9, f2, x;
  ps_muls1 f10, x, f12;
  ps_muls0 f9, f9, f5;
  fmuls f10, f10, f5;
  ps_muls0 f9, f9, f4;
  fmadds x, f8, f4, f1;
  fmuls f10, f10, f5;
  ps_madds1 x, f5, f8, x;
  fadds x, x, f9;
  ps_madds1 x, f4, f9, x;
  fmadds x, f10, f4, x;

  bge cr1, skip_neg2;
  ps_neg x, x;
skip_neg2:
  addi sp, sp, (sizeof(int) * 4);
  blr
}
#else  // __MWERKS__
// TODO: GCC Compatible asm
float sndSqrt(register float x) { return sqrt(x); }

// TODO: GCC Compatible asm
float sndCos(register float x) { return cos(x); }
#endif // __MWERKS__
#elif MUSY_TARGET == MUSY_TARGET_PC
float sndSqrt(float x) { return sqrt(x); }

float sndCos(float x) { return cos(x); }
#endif // MUSY_TARGET == MUSY_TARGET_PC
#endif // MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)

void sndConvertMs(u32 *time) { *time = *time * 256; }

void sndConvertTicks(u32 *out, SYNTH_VOICE *svoice) {
  *out = (((*out << 16) / synthGetTicksPerSecond(svoice)) * 1000) / 32;
}

u32 sndConvert2Ms(u32 time) { return time / 256; }

#ifdef __cplusplus
}
#endif // __cplusplus
