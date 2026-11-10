#ifndef GAME_TYPES_NORMAL3D_H
#define GAME_TYPES_NORMAL3D_H

class Normal3D {
public:
    Normal3D(void *desc, int flags);
    unsigned char data[0x5C];
};

#endif /* GAME_TYPES_NORMAL3D_H */
