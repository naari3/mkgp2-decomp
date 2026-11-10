#ifndef GAME_TYPES_HUDMODEL_H
#define GAME_TYPES_HUDMODEL_H

struct HudModel {
    char data[0x90];
    HudModel(int kart, int flag) {
        fn_8013CC24(this, kart, flag);
    }
};

#endif /* GAME_TYPES_HUDMODEL_H */
