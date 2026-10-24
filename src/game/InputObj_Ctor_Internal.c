typedef struct InputObj {
    void *vtbl;
    int port;
    int state[5];
    float axis[3];
} InputObj;

extern char g_InputObjectVtable[];
extern const float g_fZero;
extern void JvsInput_SetVtable(InputObj *);

InputObj *InputObj_Ctor_Internal(InputObj *self, int port) {
    JvsInput_SetVtable(self);
    self->vtbl = g_InputObjectVtable;
    self->port = port;
    self->state[0] = 0;
    self->state[1] = 0;
    self->state[2] = 0;
    self->state[3] = 0;
    self->state[4] = 0;
    self->axis[0] = g_fZero;
    self->axis[1] = g_fZero;
    self->axis[2] = g_fZero;
    return self;
}
