#ifndef GAME_TYPES_FACEMODELSUB_H
#define GAME_TYPES_FACEMODELSUB_H

struct FaceModelSub {
    char pad[0x20];
    float scale;
    void Reset();
};

#endif /* GAME_TYPES_FACEMODELSUB_H */
