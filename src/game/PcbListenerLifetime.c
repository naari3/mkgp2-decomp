/* Only the listener fields observed in the authoritative lifetime routines. */
#pragma cplusplus on
extern "C" {
struct PcbBackupView {
    unsigned char first[4];
    int socket;
    unsigned char remaining[0x22];
};
extern PcbBackupView lbl_80598A60;
extern const char lbl_806D3240[6];
int Backup_PublishShadowCopy_Inline(void);
int acClosesocket(int socket);
int TCPConn_LogError(int result, int socket, const char* operation);
void* memset(void* destination, int byte, unsigned long size);
}

struct PcbListener {
    int socket;
    int state;
    int pending;
    int acceptedSocket;
    int addressSize;
    int retries;
    int portCycle;
    int timeout;
    unsigned char addressLength;
    unsigned char addressFamily;
    unsigned short port;
    unsigned int address;
    unsigned char addressTail[8];

    PcbListener();
    ~PcbListener();
    void closeSocket();
};

inline void PcbListener::closeSocket()
{
    if (socket >= 0) {
        int result = acClosesocket(socket);
        if (result < 0) {
            TCPConn_LogError(result, socket, lbl_806D3240);
            ++retries;
            if (retries < 8) {
                return;
            }
        }
        if (++portCycle > 8) {
            portCycle = 0;
        }
        port = 5000 + portCycle;
        socket = -1;
        state = 2;
        pending = 0;
    }
}

PcbListener::~PcbListener()
{
    if (state == 5) {
        lbl_80598A60.socket = socket;
        Backup_PublishShadowCopy_Inline();
    }
    closeSocket();
}

PcbListener::PcbListener()
{
    socket = -1;
    retries = 0;
    state = 2;
    pending = 0;
    timeout = 6000;
    acceptedSocket = -1;
    portCycle = 0;
    addressSize = 16;
    memset(&addressLength, 0, 16);
    addressFamily = 2;
    port = 5000 + portCycle;
    address = 0;
    if (lbl_80598A60.socket != -1) {
        socket = lbl_80598A60.socket;
        state = 5;
        pending = 0;
        timeout = 0;
        lbl_80598A60.socket = -1;
        Backup_PublishShadowCopy_Inline();
    }
}
