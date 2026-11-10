#ifndef GAME_TYPES_EFFECTBUS_H
#define GAME_TYPES_EFFECTBUS_H

/* Declare before including (each user already does): Driver */

struct EffectBus { unsigned char opaque[88]; EffectBus(Driver *); };

#endif /* GAME_TYPES_EFFECTBUS_H */
