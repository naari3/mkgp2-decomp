#ifndef GAME_ANON_8021BC44_PRIVATE_H
#define GAME_ANON_8021BC44_PRIVATE_H

/* Keyboard/vector layout from fn_801BAA88.cpp. */
struct KeyGroup {
    struct { short x, y; int res; } img[2];
    struct { short x, y; } label;
    int x14;
    signed char cols[4];
};
template <class T> struct KeyVecBase {
    int cap;
    int count;
    T *data;
    ~KeyVecBase();
};
template <class T> struct KeyVecMid : KeyVecBase<T> { ~KeyVecMid() {} };
template <class T> struct KeyVec : KeyVecMid<T> { ~KeyVec() {} };
struct KeyBoard {
    unsigned char ascii;
    KeyVec<KeyGroup> groups;
    int group;
    int page;
    unsigned char shift;
    int lastCol;
    int saveCol;
    int saveRow;
};

#endif
