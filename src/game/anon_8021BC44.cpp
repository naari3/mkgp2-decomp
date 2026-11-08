#include "game/anon_8021BC44Types.h"

TimeAttackResult::~TimeAttackResult() {
    for (int i = 0; i < 9; i++) {
        if (digits[i] != 0) {
            delete digits[i];
            digits[i] = 0;
        }
    }
    if (credit != 0) {
        delete credit;
        credit = 0;
    }
    if (record != 0) {
        delete record;
        record = 0;
    }
    if (banner != 0) {
        delete banner;
        banner = 0;
    }
    if (entry) {
        NameEntry *e = entry;
        delete e;
    }
    if (title != 0) {
        title->Release();
    }
    if (coin != 0) {
        delete coin;
    }
}
