#ifndef GAME_TYPES_ZONEVOLUME_H
#define GAME_TYPES_ZONEVOLUME_H

#include "game/types/Vec3f.h"

/* Declare before including (each user already does): ZoneDesc */

struct ZoneVolume {
    ZoneVolume(const ZoneDesc *desc, int closed);
    ~ZoneVolume();
    unsigned char Contains(Vec3f *pos);
    void Draw();
    char pad00[0x4];
};

#endif /* GAME_TYPES_ZONEVOLUME_H */
