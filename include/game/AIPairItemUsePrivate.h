#ifndef GAME_AI_PAIR_ITEM_USE_PRIVATE_H
#define GAME_AI_PAIR_ITEM_USE_PRIVATE_H
typedef struct PairItemController { char pad[0xEC]; int itemTimer, hitTimer; } PairItemController;
typedef struct PairItemRender { char pad[0x248]; int kartId; } PairItemRender;
#endif
