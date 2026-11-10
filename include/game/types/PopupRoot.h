#ifndef GAME_TYPES_POPUPROOT_H
#define GAME_TYPES_POPUPROOT_H

struct PopupRoot {
    virtual ~PopupRoot() {}
    virtual void Finish() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void _keyR();
    unsigned int id;
    int field08;
    int field0C;
    PopupRoot(int id_) : id(id_), field08(0), field0C(0) {}
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

#endif /* GAME_TYPES_POPUPROOT_H */
