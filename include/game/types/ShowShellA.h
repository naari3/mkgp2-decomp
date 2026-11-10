#ifndef GAME_TYPES_SHOWSHELLA_H
#define GAME_TYPES_SHOWSHELLA_H

struct ShowShellA {
    char pad[0x10];
    ShowShellA(int layer, float x, float y, float scale);
    ~ShowShellA();
};

#endif /* GAME_TYPES_SHOWSHELLA_H */
