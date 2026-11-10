#ifndef GAME_TYPES_WARPERRORSTRING_H
#define GAME_TYPES_WARPERRORSTRING_H

struct WarpErrorString {
    char *ptr;
    void *control;
    WarpErrorString(void *);
    ~WarpErrorString();
};

#endif /* GAME_TYPES_WARPERRORSTRING_H */
