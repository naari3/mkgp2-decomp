#ifndef GAME_TYPES_CLCPOPTASKS_H
#define GAME_TYPES_CLCPOPTASKS_H

/* Real task interfaces used by the card popups. */
struct clYTaskInterface {
    virtual ~clYTaskInterface() {}
    unsigned int id;
    int field08;
    int field0C;
    clYTaskInterface(int id_) : id(id_), field08(0), field0C(0) {}
    bool CanDraw() {
        if (field08 > 0) {
            field08--;
            return 0;
        }
        if (field0C == 1) {
            field0C = 2;
        }
        return field0C <= 0;
    }
    bool CanUpdate() {
        if (field08 > 0) {
            return 0;
        }
        return field0C <= 0;
    }
};

struct clCTaskInterface : clYTaskInterface {
    clCTaskInterface(int id_) : clYTaskInterface(id_) {}
    virtual ~clCTaskInterface() {}
    virtual void Finish() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
};

/* Use the existing task-list declarations with their canonical task type. */
#define GAME_TYPES_POPUPROOT_H
#define GAME_TYPES_POPUPTASK_H
typedef clYTaskInterface PopupRoot;
typedef clCTaskInterface PopupTask;

#endif
