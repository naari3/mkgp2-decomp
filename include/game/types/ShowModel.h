#ifndef GAME_TYPES_SHOWMODEL_H
#define GAME_TYPES_SHOWMODEL_H

struct ShowModel {
    ShowModel(void *res, int flag);
    virtual ~ShowModel();
    char pad[0x20 - 0x4];
};

#endif /* GAME_TYPES_SHOWMODEL_H */
