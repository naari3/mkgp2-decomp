/* Observed receive fields only; no complete TCPConn layout is claimed. */
typedef struct TCPConnRecvView {
    int socket;
    unsigned char gap04[4];
    int role;
    int state;
    unsigned char gap10[0x10];
    int retries;
    int readPosition;
    int writePosition;
    unsigned char gap2C[0x14];
    unsigned char *buffer;
    int capacity;
    void *receiveBuffer;
    unsigned char gap4C;
    unsigned char pending;
} TCPConnRecvView;

typedef struct RecvTimeout { unsigned int seconds, micros; } RecvTimeout;
extern unsigned int lbl_806DCF10;
extern unsigned int lbl_806DCF14;
extern const char lbl_806D31A8[7];
extern int acPollResponse(int socket);
extern int acReadResponse(int socket);
extern int fn_80292BFC(const void *source, void *destination, int length);
extern int acSelect(int count, void *readSet, void *writeSet, void *exceptSet,
                    RecvTimeout *timeout);
extern int acRecv(int socket, void *destination, int length, int flags);
extern int TCPConn_LogError(int result, int socket, const char *operation);
extern void *memcpy(void *destination, const void *source, unsigned long length);
extern void *memset(void *destination, int fill, unsigned long length);

int TCPConn_PollRecvComplete(TCPConnRecvView *self)
{
    int received;
    unsigned short *header;
    if (self->pending == 0) return 0;
    while (acPollResponse(self->socket) != 1) {}
    received = acReadResponse(self->socket);
    if (received > 0) {
        fn_80292BFC(self->receiveBuffer, self->buffer + self->writePosition, received);
    }
    if (received == 0) {
        self->state = 0;
    } else if (received < 0) {
        if (++self->retries >= 180) self->state = 0;
    } else {
        self->writePosition += received;
        self->retries = -1;
    }
    header = (unsigned short *)(self->buffer + self->writePosition);
    header[0] = 0;
    header[1] = 0;
    self->pending = 0;
    return received;
}

static inline unsigned int TCPConn_SelectMask(unsigned int bit)
{
    return ((bit << 24) & 0xFF000000U) | ((bit << 8) & 0x00FF0000U)
         | ((bit >> 8) & 0x0000FF00U) | ((bit >> 24) & 0x000000FFU);
}

static inline unsigned int TCPConn_AddReadSocket(unsigned int *set, int socket)
{
    unsigned int index = (unsigned int)socket >> 5;
    unsigned int mask = TCPConn_SelectMask(1U << (socket & 31));
    set[index] |= mask;
    return mask;
}

static inline unsigned char TCPConn_Readable(int socket)
{
    unsigned int set[8];
    RecvTimeout timeout;
    unsigned int mask;
    int result;
    unsigned char ready = 0;
    timeout.seconds = lbl_806DCF10;
    timeout.micros = lbl_806DCF14;
    if (socket < 0) return ready;
    {
        memset(set, 0, sizeof(set));
        mask = TCPConn_AddReadSocket(set, socket);
        result = acSelect(socket + 1, set, 0, 0, &timeout);
        if (result < 0) {
            TCPConn_LogError(result, socket, lbl_806D31A8);
            ready = 0;
        } else if ((set[(unsigned int)socket >> 5] & mask) == 0) {
            ready = 0;
        } else {
            ready = 1;
        }
    }
    return ready;
}

int TCPConn_PollRecv(TCPConnRecvView *self)
{
    int result;
    if (self->role != 1) return 0;
    if (self->socket < 0) return 0;
    if (self->buffer == 0) return 0;
    if (self->state != 6) return 0;
    if (self->pending == 1) return 0;
    memcpy(self->buffer, self->buffer + self->readPosition,
           self->writePosition - self->readPosition);
    self->writePosition -= self->readPosition;
    self->readPosition = 0;
    if (TCPConn_Readable(self->socket) == 0) {
        if (++self->retries >= 180) self->state = 0;
        return 0;
    }
    result = acRecv(self->socket, self->receiveBuffer,
                    self->capacity - self->writePosition, 0);
    self->pending = 1;
    return result;
}
