#ifndef GAME_TYPES_COINPROMPTHOLDER_H
#define GAME_TYPES_COINPROMPTHOLDER_H

#include "game/types/CoinPrompt.h"

struct CoinPromptHolder {
    CoinPrompt *p;
    CoinPromptHolder(CoinPrompt *q) : p(q) {}
    ~CoinPromptHolder() throw() { fn_8023CFE0(p, 1); }
};

#endif /* GAME_TYPES_COINPROMPTHOLDER_H */
