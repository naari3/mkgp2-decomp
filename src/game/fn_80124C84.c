#pragma cplusplus on

class Obj {
public:
    virtual ~Obj();
};

extern "C" void MemoryManager_TimedFree(void *p);

struct Holder {
    Obj *obj;
};

extern "C" Holder *fn_80124C84(Holder *self, short flag)
{
    if (self != 0) {
        if (self->obj != 0) {
            delete self->obj;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
