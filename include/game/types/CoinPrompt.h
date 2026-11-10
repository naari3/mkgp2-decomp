#ifndef GAME_TYPES_COINPROMPT_H
#define GAME_TYPES_COINPROMPT_H

struct CoinPrompt {
    char body[0x20];
    CoinPrompt(int a, int b, int c, int d, int e);
};

#endif /* GAME_TYPES_COINPROMPT_H */
