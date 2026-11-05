#include "game/TCPListenPoll.h"

static inline unsigned char closeListener(TCPListenState *self)
{
    int result;
    if (self->socket < 0) return 1;
    result = acClosesocket(self->socket);
    if (result < 0) {
        TCPConn_LogError(result, self->socket, lbl_806D3240);
        ++self->retries;
        if (self->retries < 8) return 0;
    }
    if (++self->portCycle > 8) self->portCycle = 0;
    *(unsigned short *)(self->address + 2) = 5000 + self->portCycle;
    self->socket = -1;
    self->state = 2;
    self->pending = 0;
    return 1;
}
static inline unsigned char openListener(TCPListenState *self)
{
    int result;
    if (self->socket >= 0) return 1;
    result = acSocket(2, 1, 0);
    self->socket = result;
    if (result < 0) {
        TCPConn_LogError(self->socket, 0, lbl_806D3248);
        return 0;
    }
    acSetTimeOuts(self->socket, 10000, 10000, 10000);
    self->pending = 0;
    self->timeout = 6000;
    self->retries = 0;
    return 1;
}
static inline unsigned char bindListener(TCPListenState *self)
{
    int result;
    if (self->socket < 0) return 0;
    result = acBind(self->socket, self->address, 16);
    if (result < 0) {
        TCPConn_LogError(result, self->socket, lbl_806D3238);
        self->state = 1;
        return 0;
    }
    return 1;
}
static inline unsigned char listenListener(TCPListenState *self)
{
    int result;
    if (self->socket < 0) return 0;
    result = acListen(self->socket, 5);
    if (result < 0) {
        TCPConn_LogError(result, self->socket, lbl_806D3230);
        self->state = 1;
        return 0;
    }
    self->retries = 0;
    return 1;
}
static inline unsigned char acceptListener(TCPListenState *self)
{
    if (self->socket < 0) return 0;
    if (self->state == 6) return 1;
    if (self->pending == 0) {
        memset(self->acceptedAddress, 0, 16);
        acAccept(self->socket, self->acceptedAddress, &self->addressSize);
        ++self->pending;
    }
    if (self->pending == 1) {
        if (acPollResponse(self->socket) == 1) {
            self->acceptedSocket = acReadResponse(self->socket);
            if (self->acceptedSocket < 0) {
                TCPConn_LogError(self->acceptedSocket, self->socket, lbl_806D3228);
                self->pending = 0;
                if (++self->retries > self->timeout) self->state = 1;
                return 0;
            }
            self->state = 6;
            ++self->pending;
            return 1;
        }
    }
    return 0;
}
unsigned char TCPListen_Poll(TCPListenState *self, unsigned char pause)
{
    if (pause == 1) return 0;
    switch (self->state) {
    case 9: return 0;
    case 6: return 1;
    case 0: return 0;
    case 8:
        if (closeListener(self) == 1) self->state = 9;
        else return 0;
    case 1:
        if (closeListener(self) == 1) self->state = 2;
        else return 0;
    case 2:
        if (openListener(self) == 1) self->state = 3;
        else return 0;
    case 3:
        if (bindListener(self) == 1) self->state = 4;
        else return 0;
    case 4:
        if (listenListener(self) == 1) self->state = 5;
        else return 0;
    case 5:
        if (acceptListener(self) == 1) return 1;
    }
    return 0;
}
