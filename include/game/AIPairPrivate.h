#ifndef GAME_AI_PAIR_PRIVATE_H
#define GAME_AI_PAIR_PRIVATE_H
/* Private view of the eight 0x38-byte AI tracking records. */
typedef struct AIPairRecord {
    int kartId;
    void *driver;
    void *field08;
    int waypoint;
    int nearestKart;
    void *nearestDriver;
    float distanceSquared;
    int field1C;
    float field20;
    int field24;
    int field28;
    int field2C;
    int field30;
    float speedBonus;
} AIPairRecord;
#endif
