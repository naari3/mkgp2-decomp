#ifndef GAME_ACLIB_PRIVATE_H
#define GAME_ACLIB_PRIVATE_H

struct ResetState {
    char pad00[0x18];
    unsigned short kind;
    char pad1A[2];
    unsigned int error;
};

struct MediaConfig {
    int busy;
    unsigned char port0;
    unsigned char port1;
    char pad06[2];
    int (*onReset)(unsigned int error);
};

/* Request parameters are copied together between the state and length. */
struct MediaRequestParams {
    unsigned int port;
    unsigned int arg;
};

struct MediaRequest {
    unsigned int state;
    MediaRequestParams params;
    unsigned int len;
};

struct MediaRequestSlot {
    MediaRequest req;
    char pad10[0x1C];
};

extern "C" {
extern const char lbl_803F13E4[];
ResetState *fn_8028D6B0(void);
int sprintf(char *buf, const char *fmt, ...);
void OSReport(const char *fmt, ...);
void *memset(void *dst, int c, unsigned long n);
void fn_80286A74(void *info, int hot);
void fn_802947CC(void);
void fn_80286774(void);
void GXAbortFrame(void);
void VISetBlack(int black);
void VIFlush(void);
void VIWaitForRetrace(void);
void OSResetSystem(int reset, unsigned int code, int menu);
int fn_8028AA40(unsigned char board, int *a, unsigned char *b);
int fn_8028AD94(unsigned char board, unsigned char **data, unsigned char *players, unsigned char *bits);
void fn_802895E4(int id, unsigned char b, int a, unsigned int pressed);
int fn_80293BF4(void);
void fn_8028B9A4(void);
unsigned char fn_8028B0B4(void);
MediaRequest *fn_80288EAC(void);
int fn_8028A8B4(unsigned char port, unsigned char arg, unsigned short len);
void fn_8029425C(void);
int fn_80293BCC(void);
void fn_80293DD4(void);
int fn_80255000(void);
int fn_80255154(int board, int id);
}


extern "C" {
extern MediaConfig acLib_tail_bss_80679E28;
extern unsigned int acLib_nm1_bss_80679E34[8];
extern unsigned int acLib_nm1_bss_80679E54[32];
extern MediaRequestSlot acLib_tail_bss_80679ED4;
extern int acLib_tail_bss_806D1AD0;
extern int acLib_tail_bss_806D1AD4;
extern void *acLib_tail_data_806D0A90;
int fn_80294810(int a, int b, int c);
int fn_8028BAD0(void);
void fn_80289C68(int a, int b);
}

#endif
