#ifndef GAME_TYPES_GXCHANNEL_H
#define GAME_TYPES_GXCHANNEL_H

class GXChannel {
public:
    GXChannel(void *root, void *desc, int flags, int mode);
    ~GXChannel();
    void PushTransform(Mtx m);

private:
    char pad[0x14];
};

#endif /* GAME_TYPES_GXCHANNEL_H */
