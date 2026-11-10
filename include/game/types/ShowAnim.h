#ifndef GAME_TYPES_SHOWANIM_H
#define GAME_TYPES_SHOWANIM_H

struct ShowAnim {
    char pad[0x70];
    ShowAnim(int res, int a, int b, const void *data, int c);
    ~ShowAnim();
};

#endif /* GAME_TYPES_SHOWANIM_H */
