#ifndef GAME_SCENE_8016219C_PRIVATE_H
#define GAME_SCENE_8016219C_PRIVATE_H

extern "C" {
unsigned long strlen(const char *);
char *strcpy(char *, const char *);
void *FUN_8003b120(unsigned long);
void SharedPtr_Init(void *, void *);
void *Alloc(unsigned long);
}

namespace std {
struct exception {
    exception() {}
    virtual ~exception();
};
}
#include "game/types/ClStr.h"
namespace std {
struct SceneString {
    ClStr value;
    SceneString(const char *s) : value(FUN_8003b120(strlen(s) + 1)) {
        strcpy(value.ptr, s);
    }
    ~SceneString();
};
struct logic_error : exception {
    SceneString message;
    logic_error(const char *s) : message(s) {}
    virtual ~logic_error();
};
struct length_error : logic_error {
    length_error(const char *s) : logic_error(s) {}
    virtual ~length_error();
};
}

struct PointerTable162 {
    unsigned long capacity;
    unsigned long count;
    void **data;
};

#endif
