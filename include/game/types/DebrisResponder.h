#ifndef GAME_TYPES_DEBRISRESPONDER_H
#define GAME_TYPES_DEBRISRESPONDER_H

#include "game/types/DebrisVec.h"

struct DebrisResponder { void *particles; DebrisResponder(DebrisVec, DebrisVec); };

#endif /* GAME_TYPES_DEBRISRESPONDER_H */
