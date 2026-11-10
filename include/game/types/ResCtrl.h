#ifndef GAME_TYPES_RESCTRL_H
#define GAME_TYPES_RESCTRL_H

struct ResCtrl {
    void *resId;
    int field4, mode, fieldc;
    unsigned char flag, pad11[3];
    float x, y, z, width, height, field28, scaleX, scaleY;
    unsigned int colors[4];
    int tail[5];
    ResCtrl();
    ~ResCtrl() {}
};

#endif /* GAME_TYPES_RESCTRL_H */
