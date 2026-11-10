#ifndef GAME_AI_KART_INIT_PRIVATE_H
#define GAME_AI_KART_INIT_PRIVATE_H
#include "game/types/size_t.h"

void *operator new(size_t);
void operator delete(void *) throw();

struct AIPosition {
    float x, y, z;
    AIPosition() {}
    ~AIPosition() {}
};
struct AIResponder {
    void *vptr;
    char state[8];
    AIResponder(AIPosition *);
    ~AIResponder();
};
struct AIWarpResponder {
    void *vptr;
    AIWarpResponder();
    ~AIWarpResponder();
};
struct AIDriver {
    char opaque[0x308];
    AIWarpResponder *warp;
    char tail[0x384-0x30c];
    AIDriver(int, void *, float *, int, int, int);
    ~AIDriver();
};
struct AITornado {
    char opaque[0x154];
    AITornado(int, AIDriver *, void *, int, float, float, float);
    ~AITornado();
};
struct AIAudio {
    char opaque[0x38];
    AIAudio(void *, unsigned char, unsigned char, int, float *);
    ~AIAudio();
};
struct AIExtra {
    char opaque[0x58];
    AIExtra(int, int);
    ~AIExtra();
};
struct AIRun {
    virtual ~AIRun();
};
struct AIRun2 : AIRun {
    char opaque[0x194];
    AIRun2(AIDriver *, AITornado *, int, int, int);
};
struct AIRun1 : AIRun {
    char opaque[0x194];
    AIRun1(AIDriver *, AITornado *, int, int, int);
};
struct AIItem {
    virtual ~AIItem();
    char opaque[0x28];
    AIItem(AIDriver *, AITornado *, int, int);
};
struct AISteering {
    char opaque[0x118];
    AISteering(AIDriver *, AITornado *);
    ~AISteering();
};
struct AIAux {
    char opaque[0x8c];
    AIAux(AIDriver *, AITornado *);
    ~AIAux();
};
template<class T> struct AIOwn {
    T *p;
    AIOwn() {}
    ~AIOwn() throw() { delete p; }
    void reset(T *q) throw() {
        if (p != q) { delete p; p = q; }
    }
};
struct AIKart : AIResponder, AIWarpResponder {
    AIOwn<AIDriver> driver;
    AIOwn<AITornado> tornado;
    AIOwn<AIAudio> audio;
    AIOwn<AIExtra> extra;
    AIOwn<AIRun> run;
    AIOwn<AIItem> item;
    AIOwn<AISteering> steering;
    AIOwn<AIAux> aux;
    AIPosition position;
    AIPosition previous;
    float matrix[12];
    void *path;
    int pathId, kartId, characterId, arg7;
    float f8c, f90;
    unsigned char flag94;
    int f98, f9c, fa0;
    float fa4;
    int fa8, fac, fb0, fb4, fb8, fbc, fc0, fc4, fc8, fcc;
    int fd0, fd4, fd8, fdc, fe0, fe4, fe8, fec, ff0;
    AIKart(void *, int, int, int);
};
#endif
