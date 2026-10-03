/* Only fields observed by the send path are modeled. */
typedef struct TCPConnSendView {
    int socket;
    unsigned char gap04[4];
    int role;
    int state;
    unsigned char gap10[0x1C];
    int writePosition;
    int headerPosition;
    unsigned char gap34[9];
    unsigned char headerActive;
    unsigned char gap3E[2];
    unsigned char *buffer;
    int capacity;
    void *transferBuffer;
    unsigned char pending;
} TCPConnSendView;

typedef struct SendTimeout { unsigned int seconds, micros; } SendTimeout;
extern unsigned int lbl_806DCF10;
extern unsigned int lbl_806DCF14;
extern const char lbl_806D31A8[7];
extern int acSelect(int count, void *readSet, void *writeSet, void *exceptSet,
                    SendTimeout *timeout);
extern int acSend(int socket, const void *source, int length, int flags);
extern int fn_802929BC(const void *source, void *destination, int length);
extern int TCPConn_LogError(int result, int socket, const char *operation);
extern void *memset(void *destination, int fill, unsigned long length);

static inline unsigned int TCPConn_SendMask(unsigned int bit)
{
    return ((bit << 24) & 0xFF000000U) | ((bit << 8) & 0x00FF0000U)
         | ((bit >> 8) & 0x0000FF00U) | ((bit >> 24) & 0x000000FFU);
}

static inline unsigned int TCPConn_AddWriteSocket(unsigned int *set, int socket)
{
    unsigned int index = (unsigned int)socket >> 5;
    unsigned int mask = TCPConn_SendMask(1U << (socket & 31));
    set[index] |= mask;
    return mask;
}

static inline unsigned char TCPConn_Writable(int socket)
{
    unsigned int set[8];
    SendTimeout timeout;
    unsigned int mask;
    int result;
    unsigned char ready = 0;
    timeout.seconds = lbl_806DCF10;
    timeout.micros = lbl_806DCF14;
    if (socket < 0) return ready;
    memset(set, 0, sizeof(set));
    mask = TCPConn_AddWriteSocket(set, socket);
    result = acSelect(socket + 1, 0, set, 0, &timeout);
    if (result < 0) {
        TCPConn_LogError(result, socket, lbl_806D31A8);
        ready = 0;
    } else if ((set[(unsigned int)socket >> 5] & mask) == 0) {
        ready = 0;
    } else {
        ready = 1;
    }
    return ready;
}

int TCPConn_PollSend(TCPConnSendView *self)
{
    unsigned short *header;
    if (self->role != 0) return 0;
    if (self->socket < 0) return 0;
    if (self->buffer == 0) return 0;
    if (self->pending == 1) return 0;
    if (self->state != 6) return 0;
    if (self->headerActive == 0 && self->role == 0 &&
        self->capacity - self->writePosition > 4) {
        header = (unsigned short *)(self->buffer + self->writePosition);
        header[0] = 0xFFFF;
        header[1] = 4;
        self->headerPosition = self->writePosition;
        self->writePosition += 4;
        self->headerActive = 1;
    }
    self->headerActive = 0;
    if (TCPConn_Writable(self->socket) == 0) return 0;
    fn_802929BC(self->buffer, self->transferBuffer, self->writePosition);
    acSend(self->socket, self->transferBuffer, self->writePosition, 0);
    self->writePosition = 0;
    self->headerPosition = 0;
    self->pending = 1;
    return 1;
}
