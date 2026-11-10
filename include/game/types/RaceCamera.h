#ifndef GAME_TYPES_RACECAMERA_H
#define GAME_TYPES_RACECAMERA_H

struct RaceCamera {
    unsigned char data[0x2C];
    RaceCamera(float fovy, int width, float aspect, int height, void *renderTarget);
};

#endif /* GAME_TYPES_RACECAMERA_H */
