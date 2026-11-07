#ifndef GAME_TAMODE_INIT_TABLES_PRIVATE_H
#define GAME_TAMODE_INIT_TABLES_PRIVATE_H

/* Prefix of the shared race-data pool: eight cups, three classes, two rounds. */
struct TaModeRaceTables {
    RaceParams cups[8][3][2];
};
extern "C" TaModeRaceTables BATTLE;

#endif
