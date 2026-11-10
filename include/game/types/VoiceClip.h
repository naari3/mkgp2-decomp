#ifndef GAME_TYPES_VOICECLIP_H
#define GAME_TYPES_VOICECLIP_H

typedef struct VoiceClip {
    unsigned char playCount;
    char pad1[3];
    float length;
    void *path;
} VoiceClip;

#endif /* GAME_TYPES_VOICECLIP_H */
