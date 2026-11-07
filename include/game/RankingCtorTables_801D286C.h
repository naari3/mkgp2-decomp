#ifndef RANKING_CTOR_TABLES_801D286C_H
#define RANKING_CTOR_TABLES_801D286C_H

#include "game/RankingSpriteOwner_private.h"

/* View of the existing shared ranking constant pool; no storage is emitted. */
struct RankingCtorTables {
    char earlierTables[0x4EC];
    RankingPlacement placements[4];
    short screenParams[4][3];
    short labels[24];
    short resources[16];
};

#endif
