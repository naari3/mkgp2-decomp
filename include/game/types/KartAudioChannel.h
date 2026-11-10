#ifndef GAME_TYPES_KARTAUDIOCHANNEL_H
#define GAME_TYPES_KARTAUDIOCHANNEL_H

struct SoundSource;

/* Merged from 6 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct KartAudioChannel KartAudioChannel;
struct KartAudioChannel {
    /* 0x000 */ void *owner;
    /* 0x004 */ unsigned char muted;  /* also: playerType */
    /* 0x005 */ unsigned char enabled;
    /* 0x006 */ unsigned char flag6;
    /* 0x007 */ unsigned char pad_007[0x1];
    /* 0x008 */ int channel;
    /* 0x00C */ struct SoundSource *source;  /* also: mtx */
    /* 0x010 */ float targetVol;  /* also: volume */
    /* 0x014 */ float vol;  /* also: pitch */
    /* 0x018 */ unsigned char playing;  /* also: active */
    /* 0x019 */ unsigned char pad_019[0x3];
    /* 0x01C */ float targetPitch;  /* also: volume2 */
    /* 0x020 */ float pitch;  /* also: pitch2 */
    /* 0x024 */ int mode;  /* also: state */
    /* 0x028 */ int pendingStopSE;
    /* 0x02C */ int stopTimer;
    /* 0x030 */ int skidState;  /* also: jumpKind */
    /* 0x034 */ int surfaceSE;
};

#endif /* GAME_TYPES_KARTAUDIOCHANNEL_H */
