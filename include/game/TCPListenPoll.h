#ifndef GAME_TCPLISTENPOLL_H
#define GAME_TCPLISTENPOLL_H
/* Listener layout shared conceptually with PcbListenerLifetime.c. */
typedef struct TCPListenState {
    int socket, state, pending, acceptedSocket, addressSize;
    int retries, portCycle, timeout;
    unsigned char address[16];
    unsigned char acceptedAddress[16];
} TCPListenState;
extern int acClosesocket(int);
extern int acSocket(int, int, int);
extern int acSetTimeOuts(int, int, int, int);
extern int acBind(int, void *, int);
extern int acListen(int, int);
extern int acAccept(int, void *, int *);
extern int acPollResponse(int);
extern int acReadResponse(int);
extern int TCPConn_LogError(int, int, const char *);
extern void *memset(void *, int, unsigned long);
extern const char lbl_806D3240[6], lbl_806D3248[7], lbl_806D3238[5];
extern const char lbl_806D3230[7], lbl_806D3228[7];
#endif
