#ifndef GAME_TYPES_FADEKEYBASE_H
#define GAME_TYPES_FADEKEYBASE_H

struct FadeKeyBase {
    virtual ~FadeKeyBase();
    int dur;
    FadeKeyBase(int d) : dur(d) {}
};

#endif /* GAME_TYPES_FADEKEYBASE_H */
