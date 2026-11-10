#ifndef GAME_TYPES_CAMERA_H
#define GAME_TYPES_CAMERA_H

struct Camera { char data[0x2C]; Camera(float a, float b, int w, int h, int target); };

#endif /* GAME_TYPES_CAMERA_H */
