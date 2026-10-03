extern void* memset(void* destination, int value, unsigned long size);

/* Observed TCP connection fields, not a complete runtime class declaration. */
typedef struct TCPConnCloseView {
    int socket;
    int retry;
    int mode;
    int state;
    int countdown;
    int channel;
    int field18;
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
    unsigned char pad3F;
    void* buffer;
    int bufferSize;
    int destination;
    unsigned char field4C;
    unsigned char field4D;
    unsigned char pad4E[2];
    unsigned char addressLength;
    unsigned char addressFamily;
    unsigned short port;
    unsigned int address;
    unsigned char addressTail[8];
} TCPConnCloseView;

extern int acClosesocket(int socket);
extern int acSetTimeOuts(int socket, int send, int receive, int connect);
extern int TCPConn_LogError(int result, int socket, const char* message);
extern int TCPConn_FreeTxBuffer(void* buffer);
extern void* TCPConn_AllocTxBuffer(int* size);
extern int TCPConn_GetChannelDest(int channel, int mode);
extern unsigned int PcbIdToIp_GetCached(int channel);
extern const char lbl_806D31B8[6];

static inline void TCPConn_CloseSocket(TCPConnCloseView* self)
{
    int result;
    if (self->active != 0) {
        if (self->socket >= 0) {
            result = acClosesocket(self->socket);
            if (result < 0) {
                TCPConn_LogError(result, self->socket, lbl_806D31B8);
                ++self->retry;
                if (self->retry < 4) {
                    return;
                }
            }
            if (self->cycleEnabled != 0) {
                if (--self->portCycle < 0) {
                    self->portCycle = 8;
                }
                self->port = 5000 + self->portCycle;
            }
            self->cycleEnabled = 1;
            self->socket = -1;
            self->retry = 0;
            self->countdown = 5;
            self->state = 9;
            if (++self->closeCount >= 16) {
                self->state = 10;
            }
        }
    }
}

void TCPConn_Close(TCPConnCloseView* self)
{
    if (self->active != 0) {
        TCPConn_CloseSocket(self);
        TCPConn_FreeTxBuffer(self->buffer);
        self->buffer = 0;
        self->active = 0;
    }
}

void TCPConn_Init(TCPConnCloseView* self, int channel, int socket, int mode)
{
    if (self->active == 1) {
        return;
    }
    if (socket < 0) {
        self->state = 2;
    } else {
        self->state = 6;
        acSetTimeOuts(socket, 80000, 80000, 80000);
    }
    self->buffer = TCPConn_AllocTxBuffer(&self->bufferSize);
    self->socket = socket;
    self->retry = 0;
    self->channel = channel;
    self->field18 = 0;
    self->mode = mode;
    self->destination = TCPConn_GetChannelDest(channel, mode);
    self->field4C = 0;
    self->field4D = 0;
    self->portCycle = 8;
    self->closeCount = 0;
    self->cycleEnabled = 1;
    self->active = 1;
    self->field1C = 1;
    self->field20 = -1;
    self->field24 = 0;
    self->field28 = 0;
    self->field2C = 0;
    self->field30 = 0;
    self->field3D = 0;
    memset(&self->addressLength, 0, 16);
    self->addressFamily = 2;
    self->port = 5000 + self->portCycle;
    self->address = PcbIdToIp_GetCached(self->channel);
}
