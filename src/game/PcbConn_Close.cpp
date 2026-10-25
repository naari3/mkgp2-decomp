/* TCP connection destructor, 0x80087760..0x80087880. */

extern "C" {
int acClosesocket(int socket);
int TCPConn_LogError(int result, int socket, const char *message);
int TCPConn_FreeTxBuffer(void *buffer);
extern const char lbl_806D31B8[6];
}

class PcbConn {
public:
    ~PcbConn();

    inline void CloseSocket()
    {
        int result;

        if (m_active != 0) {
            if (m_socket >= 0) {
                result = acClosesocket(m_socket);
                if (result < 0) {
                    TCPConn_LogError(result, m_socket, lbl_806D31B8);
                    ++m_retry;
                    if (m_retry < 4) {
                        return;
                    }
                }
                if (m_cycleEnabled != 0) {
                    if (--m_portCycle < 0) {
                        m_portCycle = 8;
                    }
                    m_port = 5000 + m_portCycle;
                }
                m_cycleEnabled = 1;
                m_socket = -1;
                m_retry = 0;
                m_countdown = 5;
                m_state = 9;
                if (++m_closeCount >= 16) {
                    m_state = 10;
                }
            }
        }
    }

    inline void Close()
    {
        if (m_active != 0) {
            CloseSocket();
            TCPConn_FreeTxBuffer(m_buffer);
            m_buffer = 0;
            m_active = 0;
        }
    }

    int m_socket;
    int m_retry;
    int m_mode;
    int m_state;
    int m_countdown;
    unsigned char pad_14[0x20];
    int m_portCycle;
    int m_closeCount;
    unsigned char m_cycleEnabled;
    unsigned char m_field3D;
    unsigned char m_active;
    unsigned char m_pad3F;
    void *m_buffer;
    unsigned char pad_44[0xE];
    unsigned short m_port;
};

PcbConn::~PcbConn()
{
    Close();
}
