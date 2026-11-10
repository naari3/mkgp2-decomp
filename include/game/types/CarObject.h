#ifndef GAME_TYPES_CAROBJECT_H
#define GAME_TYPES_CAROBJECT_H

struct CarObject {
    char data[0x118];
    CarObject(int disp, int chara, int cc, int a, int b, int c, int d, int e, float x, float z, float yaw);
};

#endif /* GAME_TYPES_CAROBJECT_H */
