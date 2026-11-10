#ifndef GAME_TYPES_SHOWSHELLB_H
#define GAME_TYPES_SHOWSHELLB_H

struct ShowShellB {
    char pad[0xC];
    ShowShellB(int layer, float x, float y, float scale);
    ~ShowShellB();
};

#endif /* GAME_TYPES_SHOWSHELLB_H */
