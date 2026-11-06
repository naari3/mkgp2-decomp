#ifndef GAME_MODE_BASE_PRIVATE_H
#define GAME_MODE_BASE_PRIVATE_H

/* Player print allowance, shared with CardPrintFlowUpdate's signed-byte view. */
struct GameModePlayerData {
    unsigned char prefix[0x198];
    signed char remaining;
    void DecrementRemaining() {
        if (remaining > 0) {
            --remaining;
        }
    }
};

#endif
