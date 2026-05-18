struct InputObject;

extern struct InputObject **g_inputManager;

struct InputObject **GetInputManager(void) {
    return g_inputManager;
}
