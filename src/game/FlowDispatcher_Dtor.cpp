extern "C" void MemoryManager_TimedFree(void *p);

class FlowObject {
public:
    virtual void v0();
    virtual void v1();
    virtual ~FlowObject();
};

struct FlowDispatcher {
    unsigned char pad_0[8];
    FlowObject *current;
    unsigned char pad_C[4];
    FlowObject *next;
};

/* 0x8002C554: deleting destructor of the flow dispatcher. */
extern "C" FlowDispatcher *FlowDispatcher_Dtor(FlowDispatcher *self, short flag)
{
    if (self != 0) {
        if (self->current != 0) {
            delete self->current;
        }
        if (self->next != 0) {
            delete self->next;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
