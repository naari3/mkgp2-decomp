#ifndef GAME_TYPES_ITEMSELECT_H
#define GAME_TYPES_ITEMSELECT_H

struct ItemSelect {
    unsigned char data[0x88];
    ItemSelect(int slot, int flag);
};

#endif /* GAME_TYPES_ITEMSELECT_H */
