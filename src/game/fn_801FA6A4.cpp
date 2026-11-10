/* Card scene's second step: track result, then select the next sequence. */
struct StepSeq { void Add(void *, int); };
struct Obj801FA6A4 { char pad[0x48]; Obj801FA6A4(int, int); };
#include "game/types/CardScene.h"
extern "C" {
extern int lbl_806D00C8, lbl_806D00D0, lbl_806D00F0;
void *fn_801F4DC0(void *, int);
char *fn_80271340(void *, int, void *, void *, int);
void fn_801FEF18(void *, int);
char *fn_801FE404();
int Sci2Card_GetUnpackStatusCode();
unsigned char Sci2Card_GetReceiptTestFlag();
void fn_8020A7CC(void *, int, int, int);
void fn_80203F5C(int);
void *fn_801FC1E0(int);
void fn_80202A5C(int);
}
extern "C" void fn_801FA6A4(CardScene *self) {
    void *p = fn_801F4DC0(self->seq, 2);
    if (p) self->result = *(int *)(fn_80271340(p, 0, &lbl_806D00F0, &lbl_806D00C8, 0) + 0x24);
    int n = 0;
    if (p) n = *(int *)(fn_80271340(p, 0, &lbl_806D00F0, &lbl_806D00C8, 0) + 0x20);
    void *o = fn_801F4DC0(self->seq, 8);
    if (o) fn_801FEF18(fn_80271340(o, 0, &lbl_806D00D0, &lbl_806D00C8, 0), n);
    if (!p) {
        p = (void *)*(int *)(fn_801FE404() + 0x16C);
        if (self->result == 0) {
            if (Sci2Card_GetUnpackStatusCode() == 5) {
                if ((int)p == 2) self->state = 8;
                else {
                    p = self->seq;
                    ((StepSeq *)p)->Add(new Obj801FA6A4(0, 4), 0);
                    fn_80202A5C(0x10);
                    self->state = 5;
                }
            } else self->state = 8;
        } else if ((int)p == 2) self->state = 8;
        else if (Sci2Card_GetReceiptTestFlag()) {
            fn_8020A7CC(self->fade, 0, 0x78, 0x78);
            fn_80203F5C(10);
            self->state = 1;
        } else {
            p = self->seq;
            ((StepSeq *)p)->Add(fn_801FC1E0(3), 0);
            self->state = 4;
            fn_80202A5C(0x11);
        }
    }
}
