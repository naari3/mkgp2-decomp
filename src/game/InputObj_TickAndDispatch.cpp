class InputDevice {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void Dispatch();
};

struct InputObj {
    InputDevice *device;
};

extern "C" void JvsInput_TickPoll(InputObj *);

extern "C" void InputObj_TickAndDispatch(InputObj *input) {
    JvsInput_TickPoll(input);
    input->device->Dispatch();
}
