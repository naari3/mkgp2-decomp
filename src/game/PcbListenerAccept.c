/* Minimal word layout observed in the two leaf functions. */
typedef struct PcbListenerAcceptView {
    int socket;
    int state;
    int pending;
    int acceptedSocket;
} PcbListenerAcceptView;

int PcbListener_TakeAcceptedSocket(PcbListenerAcceptView* self)
{
    if (self->state != 6) {
        return -1;
    }
    return self->acceptedSocket;
}

int PCBCheck_StateSet(PcbListenerAcceptView* self)
{
    if (self->socket < 0) {
        return 0;
    }
    if (self->state == 6) {
        self->pending = 0;
        self->state = 5;
    } else if (self->state == 9) {
        self->pending = 0;
        self->state = 2;
    }
    return 1;
}
