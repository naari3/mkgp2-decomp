typedef struct DebrisArray {
    unsigned char _pad[0xCC];
    void *responder;
} DebrisArray;

extern void clItemBoxResponder_Rebind(void *responder);

#pragma exceptions on
void DebrisArray_DrawForward(DebrisArray *self) {
    clItemBoxResponder_Rebind(self->responder);
}
#pragma exceptions reset
