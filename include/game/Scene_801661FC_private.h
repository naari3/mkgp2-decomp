#ifndef SCENE_801661FC_PRIVATE_H
#define SCENE_801661FC_PRIVATE_H
struct ParamModel {
    virtual ~ParamModel();
    char pad04[0x1c];
    ParamModel(void *, int);
};
struct ParamValues { float v[7]; };
struct ParamEditScene {
    void Update();
    void *vtable;
    char pad04[8];
    int done;
    unsigned char quit;
    char pad11[3];
    int text;
    int item;
    ParamModel *model;
    int repeat;
    int cursor;
    int editRepeat;
    ParamValues *table;
};
#endif
