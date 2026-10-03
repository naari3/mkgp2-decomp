/* Only fields observed in the polling state machine are modeled here. */
typedef struct TCPConnPollView {
    int socket;
    int retry;
    int mode;
    int state;
    int countdown;
    int channel;
    int connectPhase;
    int field1C;
    int field20;
    int field24;
    int field28;
    int field2C;
    int field30;
    int portCycle;
    int closeCount;
    unsigned char cycleEnabled;
    unsigned char field3D;
    unsigned char active;
    unsigned char pad3F[0x11];
    unsigned char addressLength;
    unsigned char addressFamily;
    unsigned short port;
    unsigned char addressTail[12];
} TCPConnPollView;

extern int acClosesocket(int socket);
extern int acSocket(int family, int type, int protocol);
extern int acSetTimeOuts(int socket, int send, int receive, int connect);
extern int acConnect(int socket, const void* address, int length);
extern int acPollResponse(int socket);
extern int acReadResponse(int socket);
extern int TCPConn_LogError(int result, int socket, const char* message);
extern const char lbl_806D31B8[6];
extern const char lbl_806D31C0[5];
extern const char lbl_806D31B0[8];

static inline unsigned char TCPConn_PollClose(TCPConnPollView* self)
{
    int result;
    if (self->active == 0) return 0;
    if (self->socket < 0) return 1;
    result = acClosesocket(self->socket);
    if (result < 0) {
        TCPConn_LogError(result, self->socket, lbl_806D31B8);
        ++self->retry;
        if (self->retry < 4) return 0;
    }
    if (self->cycleEnabled != 0) {
        if (--self->portCycle < 0) self->portCycle = 8;
        self->port = 5000 + self->portCycle;
    }
    self->cycleEnabled = 1;
    self->socket = -1;
    self->retry = 0;
    self->countdown = 5;
    self->state = 9;
    if (++self->closeCount >= 16) {
        self->state = 10;
        return 0;
    }
    return 1;
}

static inline unsigned char TCPConn_PollOpen(TCPConnPollView* self)
{
    if (self->socket >= 0) return 1;
    if ((self->socket = acSocket(2, 1, 0)) < 0) {
        TCPConn_LogError(self->socket, 0, lbl_806D31C0);
        return 0;
    }
    acSetTimeOuts(self->socket, 6000, 6000, 6000);
    self->connectPhase = 0;
    self->retry = 0;
    self->field1C = 1;
    self->field20 = -1;
    self->field24 = 0;
    self->field28 = 0;
    self->field2C = 0;
    self->field30 = 0;
    self->field3D = 0;
    return 1;
}

static inline unsigned char TCPConn_PollConnect(TCPConnPollView* self)
{
    int result;
    if (self->socket < 0) return 0;
    if (self->state == 6) return 1;
    if (self->connectPhase == 0) {
        acConnect(self->socket, &self->addressLength, 16);
        ++self->connectPhase;
    }
    if (self->connectPhase == 1) {
        if (acPollResponse(self->socket) == 1) {
            result = acReadResponse(self->socket);
            if (result < 0) {
                TCPConn_LogError(result, self->socket, lbl_806D31B0);
                self->state = 1;
                return 0;
            }
            acSetTimeOuts(self->socket, 80000, 80000, 80000);
            self->state = 6;
            self->cycleEnabled = 0;
            self->field1C = 1;
            self->field20 = -1;
            self->field24 = 0;
            self->field28 = 0;
            self->field2C = 0;
            self->field30 = 0;
            self->field3D = 0;
            return 1;
        }
    }
    return 0;
}

unsigned char TCPConn_Poll(TCPConnPollView* self, unsigned char tick)
{
    if (self->active == 0) return 0;
    switch (self->state) {
    case 6: return 1;
    case 0: return 0;
    case 10: return 0;
    case 1:
        if (TCPConn_PollClose(self) == 1) self->state = 9;
        else return 0;
    case 9:
        if (tick == 1 && --self->countdown <= 0) self->state = 2;
        else return 0;
    case 2:
        if (TCPConn_PollOpen(self) == 1) self->state = 7;
        else return 0;
    case 7:
        if (TCPConn_PollConnect(self) == 1) return 1;
        break;
    default: break;
    }
    return 0;
}
