#include "game/clsound_spatial_private.h"
typedef struct ClSoundQueue { unsigned int id; int state, delay; } ClSoundQueue;
extern ClSoundQueue ClSound_InitSoundSystem_bss_80677F40[37];
extern unsigned char lbl_80598A60[];
extern unsigned char lbl_806CFCA0, lbl_806D16C0;
extern const float lbl_806D94F8;
extern const char lbl_8037CFF4[];
extern void DebugPrintf(const char*, ...);
extern int OSDisableInterrupts(void);
extern void OSRestoreInterrupts(int);
extern unsigned int sndFXCheck(unsigned int);
extern unsigned char sndFXKeyOff(unsigned int);
extern unsigned int sndFXStartEx(unsigned short, unsigned int, unsigned char, unsigned char);
extern void sndFXCtrl(unsigned int, unsigned char, unsigned int);
extern void sndFXCtrl14(unsigned int, unsigned char, unsigned short);
extern int Clamp_Int(int,int,int);

static inline void ResetVoice(ClSoundVoice* voice) {
    voice->id=-1;
    voice->group=255;
    voice->category=255;
    voice->flags=0;
}
static inline void RemoveQueued(unsigned int id) {
    int i;
    for (i=0;i<37;i++) {
        if (ClSound_InitSoundSystem_bss_80677F40[i].id == -1) break;
        if (id == ClSound_InitSoundSystem_bss_80677F40[i].id) {
            ClSoundQueue *q;
            ClSoundQueue *e;
            ClSound_InitSoundSystem_bss_80677F40[i].state=3;
            ClSound_InitSoundSystem_bss_80677F40[i].delay=0;
            q=ClSound_InitSoundSystem_bss_80677F40;
            e=&q[i];
            for (;i>0;e--) {
                ClSoundQueue tmp;
                int k;
                if (e[-1].state == 3) break;
                k=i-1;
                tmp=*e;
                i--;
                e->id=q[k].id;
                e->state=q[k].state;
                e->delay=q[k].delay;
                q[k]=tmp;
            }
            break;
        }
    }
}
void fn_80190D24(void) {
    int interrupts;
    int i;
    ClSoundVoice* voice;
    unsigned int id;
    interrupts=OSDisableInterrupts();
    for (i=0;i<32;i++) {
        voice=&ClSound_InitSoundSystem_bss_80678378[i];
        if (voice->id == -1) continue;
        id=voice->id & ~0x78000000;
        if ((voice->flags & 6)==2) {
            if (voice->handle == -1 || sndFXCheck(voice->handle)==-1) {
                ResetVoice(voice);
                continue;
            }
            { unsigned int step=(voice->flags >> 11)&7;
            if (voice->volume > step) {
                voice->volume -= step;
                voice->flags |= 0x10;
            } else {
                voice->volume=0;
                voice->flags |= 0x10;
                voice->flags=(voice->flags & ~6)|4;
            }
            }
        } else if ((voice->flags & 6)==4) {
            if (voice->handle == -1 || sndFXCheck(voice->handle)==-1) {
                ResetVoice(voice);
                continue;
            }
            if (voice->volume) {
                voice->volume=0;
                voice->flags |= 0x10;
            } else {
                if (sndFXKeyOff(voice->handle)) ResetVoice(voice);
                continue;
            }
        } else {
            if (voice->delay) voice->delay--;
            if (voice->handle == -1) {
                if (voice->id != 1 && voice->id != 2) {
                    if (voice->category == 0 || voice->category == 1) {
                        voice->handle=sndFXStartEx(lbl_80379554[id].effect,(int)((float)lbl_80379554[id].volume*((float)lbl_80598A60[0x2f]*lbl_806D94F8)),255,0);
                    } else {
                        voice->handle=sndFXStartEx(lbl_80379554[id].effect,lbl_80379554[id].volume,255,0);
                    }
                } else {
                    voice->handle=sndFXStartEx(lbl_80379554[id].effect,lbl_80379554[id].volume,255,0);
                }
                if (voice->handle == -1) {
                    DebugPrintf(lbl_8037CFF4,lbl_80379554[id].effect);
                    continue;
                }
            } else if (sndFXCheck(voice->handle)==-1) {
                voice->handle=-1;
                if ((lbl_80379554[id].attributes&1) && !(voice->flags&0x400)) {
                    voice->flags |= ((lbl_80379554[id].attributes&2)?0:0x200)|0x410;
                    if (voice->pan != 64) voice->flags |= 0x20;
                    if (voice->surround != 64) voice->flags |= 0x40;
                    if (voice->pitch != 0x2000) voice->flags |= 0x80;
                    if (voice->speed != 0x2000) voice->flags |= 0x100;
                    continue;
                }
                RemoveQueued(voice->id);
                ResetVoice(voice);
                continue;
            }
        }
        if (voice->flags & 0x3f0) {
            if (voice->flags & 0x10) {
                unsigned int volume;
                unsigned char scaled=(lbl_806CFCA0*(voice->volume*voice->scale)) >> 14;
                if (lbl_80379554[id].mode==0) volume=(unsigned char)Clamp_Int(scaled,0,127);
                else volume=(unsigned char)Clamp_Int(scaled,0,127);
                if (voice->id != 1 && voice->id != 2 && (voice->category==0 || voice->category==1)) {
                    float gain, level, setting, product;
                    gain = lbl_806D94F8;
                    level = (float)(unsigned char)volume;
                    setting = (float)lbl_80598A60[0x2f];
                    product = level * setting;
                    volume = (int)(product * gain);
                }
                sndFXCtrl(voice->handle,7,volume);
                voice->flags &= ~0x10;
            }
            if (voice->flags & 0x20) { sndFXCtrl(voice->handle,10,voice->pan); voice->flags &= ~0x20; }
            if (voice->flags & 0x40) { sndFXCtrl(voice->handle,0x83,voice->surround); voice->flags &= ~0x40; }
            if (voice->flags & 0x80) { sndFXCtrl14(voice->handle,0x80,voice->pitch); voice->flags &= ~0x80; }
            if (voice->flags & 0x100) { sndFXCtrl14(voice->handle,0x84,voice->speed); voice->flags &= ~0x100; }
            if (voice->flags & 0x200) {
                if (lbl_806D16C0) sndFXCtrl(voice->handle,0x5b,127);
                else sndFXCtrl(voice->handle,0x5b,0);
                voice->flags &= ~0x200;
            }
        }
    }
    OSRestoreInterrupts(interrupts);
}
