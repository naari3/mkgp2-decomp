/* Native C++ ownership for the input manager and its virtual input object. */
#pragma cplusplus on
void *operator new(unsigned long);
void operator delete(void *);
extern "C" void JvsInput_ResetCalibration(void);
extern "C" void InputMgr_TeardownStub(void);
struct InputObject {
    InputObject(int);
    virtual ~InputObject();
    char payload[0x24];
};
struct InputManager {
    InputObject *input;
    InputManager() { JvsInput_ResetCalibration(); input = new InputObject(0); }
    ~InputManager() { delete input; InputMgr_TeardownStub(); }
};
extern "C" {
extern InputManager *g_inputManager;
InputManager *GetInputManager(void) { return g_inputManager; }
void InputMgr_Shutdown(void) { delete g_inputManager; g_inputManager = 0; }
void InputMgr_Init(void) { if (!g_inputManager) g_inputManager = new InputManager; }
}
