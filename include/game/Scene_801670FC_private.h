#ifndef SCENE_801670FC_PRIVATE_H
#define SCENE_801670FC_PRIVATE_H
struct SoundDebugScene {
    void *vtable;
    char pad04[8];
    int done;
    unsigned char quit;
    char pad11[3];
    void *text;
    int soundId;
    int repeat;
};
#endif
