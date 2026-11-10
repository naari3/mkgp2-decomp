/* SoundMgr_PlaySE_Positional @ 0x800DFD28: start a sound effect and set its
 * volume and pan from a world position.
 *
 * The position is moved into camera space with the active camera's 4x4
 * matrix; the distance gives the volume (full at 0, silent at 800 units) and
 * the camera-space x/z give the two pan values (64 = centre), each clamped
 * to 0..127.  SE 0xBF is special-cased; ch > 0 tags the id with a channel.
 */

typedef unsigned int u32;
#include "game/types/Vec.h"

typedef struct CameraMatrices {
    float proj[4][4]; /* 0x00 */
    float view[4][4]; /* 0x40 */
} CameraMatrices;

extern CameraMatrices lbl_805DF3D0;

extern void SoundMgr_PlaySE(u32 se);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec in);
extern float Vec3_Magnitude_Wrapper(Vec *v);
extern void fn_8016C444(int);
extern void fn_8016C1B0(u32 se, int volume);
extern void fn_8016C168(u32 se, int pan);
extern void fn_8016C120(u32 se, int pan);

#pragma exceptions on
void SoundMgr_PlaySE_Positional(u32 se, Vec pos, int ch)
{
    Vec local;
    float volume;
    float pan_x;
    float pan_z;

    if (se == 0) {
        return;
    }
    if (se == 0xBF) {
        fn_8016C444(1);
        return;
    }
    if (ch > 0) {
        se |= (ch & 0xF) << 27;
    }
    SoundMgr_PlaySE(se);

    Mtx44_TransformVec3(&local, lbl_805DF3D0.view, pos);

    volume = 127.0f - 127.0f * ((Vec3_Magnitude_Wrapper(&local) - 400.0f) / 400.0f);
    if (volume < 0.0f) {
        volume = 0.0f;
    }
    if (127.0f < volume) {
        volume = 127.0f;
    }

    pan_x = 0.5f * -local.x + 64.0f;
    if (pan_x < 0.0f) {
        pan_x = 0.0f;
    }
    if (127.0f < pan_x) {
        pan_x = 127.0f;
    }

    pan_z = 0.5f * local.z + 64.0f;
    if (pan_z < 0.0f) {
        pan_z = 0.0f;
    }
    if (127.0f < pan_z) {
        pan_z = 127.0f;
    }

    fn_8016C1B0(se, (int)volume);
    fn_8016C168(se, (int)pan_x);
    fn_8016C120(se, (int)pan_z);
}
#pragma exceptions reset

#ifndef __MWERKS__
/* MWCC passes a struct argument as the address of a copy the caller makes.
 * Many callers were written from the disassembly and do exactly that by hand:
 * they declare the position as a pointer and pass the address of their own
 * copy. Under MWCC that is the same call. Elsewhere those units are pointed
 * at this entry (`#define SoundMgr_PlaySE_Positional
 * SoundMgr_PlaySE_Positional_ByAddress` in front of their prototype). */
void SoundMgr_PlaySE_Positional_ByAddress(u32 se, const Vec *pos, int ch)
{
    SoundMgr_PlaySE_Positional(se, *pos, ch);
}
#endif
