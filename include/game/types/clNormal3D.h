#ifndef GAME_TYPES_CLNORMAL3D_H
#define GAME_TYPES_CLNORMAL3D_H

struct clNormal3D {
    char _opaque[0x5C];
    clNormal3D(const char *res, int flags);
    ~clNormal3D();
};

#endif /* GAME_TYPES_CLNORMAL3D_H */
