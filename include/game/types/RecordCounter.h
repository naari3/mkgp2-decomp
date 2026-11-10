#ifndef GAME_TYPES_RECORDCOUNTER_H
#define GAME_TYPES_RECORDCOUNTER_H

class RecordCounter {
public:
    virtual void v8();
    virtual void vC();
    virtual void Start();
    virtual void v14();
    int f4;
    int busy;
    int count;
    bool Tick() {
        if (busy > 0) {
            busy--;
            return 0;
        }
        if (count == 1) {
            count = 2;
        }
        return count <= 0;
    }
    bool Idle() {
        if (busy > 0) {
            return 0;
        }
        return count <= 0;
    }
};

#endif /* GAME_TYPES_RECORDCOUNTER_H */
