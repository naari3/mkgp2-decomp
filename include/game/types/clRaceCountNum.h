#ifndef GAME_TYPES_CLRACECOUNTNUM_H
#define GAME_TYPES_CLRACECOUNTNUM_H

/* RTTI names and layout from the original task interfaces. The non-inline
 * interface methods keep their tables in the existing interface unit. */
struct clYTaskInterface {
    virtual ~clYTaskInterface() {}
    virtual void Finish();
    virtual void Update();
    virtual void Draw();
    unsigned int id;
    int field08;
    int field0C;
    clYTaskInterface(int id_) : id(id_), field08(0), field0C(0) {}
};

struct clCTaskInterface : clYTaskInterface {
    clCTaskInterface(int id_) : clYTaskInterface(id_) {}
    virtual ~clCTaskInterface() {}
    virtual void Finish();
};

#endif
