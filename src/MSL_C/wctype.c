#include "global.h"
#include <cctype>

/* Wide character classification table (same flags as __ctype_map). */
#define ctrl __control_char
#define motn __motion_char
#define spac __space_char
#define punc __punctuation
#define digi __digit
#define hexd __hex_digit
#define lowc __lower_case
#define uppc __upper_case
#define dhex (hexd | digi)
#define uhex (hexd | uppc)
#define lhex (hexd | lowc)

unsigned short __wctype_map[256] = {
    // clang-format off
    ctrl, ctrl, ctrl, ctrl, ctrl, ctrl, ctrl, ctrl, ctrl, motn, motn, motn, motn, motn, ctrl, ctrl,
    ctrl, ctrl, ctrl, ctrl, ctrl, ctrl, ctrl, ctrl, ctrl, ctrl, ctrl, ctrl, ctrl, ctrl, ctrl, ctrl,
    spac, punc, punc, punc, punc, punc, punc, punc, punc, punc, punc, punc, punc, punc, punc, punc,
    dhex, dhex, dhex, dhex, dhex, dhex, dhex, dhex, dhex, dhex, punc, punc, punc, punc, punc, punc,
    punc, uhex, uhex, uhex, uhex, uhex, uhex, uppc, uppc, uppc, uppc, uppc, uppc, uppc, uppc, uppc,
    uppc, uppc, uppc, uppc, uppc, uppc, uppc, uppc, uppc, uppc, uppc, punc, punc, punc, punc, punc,
    punc, lhex, lhex, lhex, lhex, lhex, lhex, lowc, lowc, lowc, lowc, lowc, lowc, lowc, lowc, lowc,
    lowc, lowc, lowc, lowc, lowc, lowc, lowc, lowc, lowc, lowc, lowc, punc, punc, punc, punc, ctrl,
    // clang-format on
};
