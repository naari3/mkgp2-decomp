extern void* memcpy(void* destination, const void* source, unsigned long length);

/* Only fields observed by the enqueue routine. */
typedef struct TCPConnEnqueueView {
    unsigned char pad00[8];
    int mode;
    unsigned char pad0C[0x20];
    int writePosition;
    int previousPosition;
    unsigned char pad34[9];
    unsigned char pending;
    unsigned char pad3E[2];
    unsigned char* buffer;
    int capacity;
} TCPConnEnqueueView;

typedef struct TCPMessageHeader {
    unsigned short type;
    unsigned short size;
} TCPMessageHeader;

int TCPConn_EnqueueMessage(TCPConnEnqueueView* self, unsigned short type,
                          unsigned short length, const void* source)
{
    unsigned short total;
    TCPMessageHeader* header;

    if (self->mode != 0) {
        return 0;
    }
    if (length != 0 && source == 0) {
        return 0;
    }
    total = length + sizeof(TCPMessageHeader);
    if (total >= self->capacity - self->writePosition) {
        return 0;
    }
    header = (TCPMessageHeader*)(self->buffer + self->writePosition);
    header->type = type;
    header->size = total;
    if (length != 0) {
        memcpy(header + 1, source, length);
    }
    self->previousPosition = self->writePosition;
    self->writePosition += total;
    self->pending = 1;
    return 1;
}
