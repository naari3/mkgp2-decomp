#ifndef GAME_TYPES_SPRITEHOLDER_H
#define GAME_TYPES_SPRITEHOLDER_H

struct SpriteHolder {
    void *s;
    SpriteHolder(void *p) : s(p) {}
    ~SpriteHolder() throw();
};

#endif /* GAME_TYPES_SPRITEHOLDER_H */
