#ifndef GAME_GPPLEASEUPDATE_PRIVATE_H
#define GAME_GPPLEASEUPDATE_PRIVATE_H

struct PlayerCharacterView {
    unsigned char pad[0x1b8];
    unsigned char character;
    void SetCharacter(int value) { character = value; }
};

#endif
