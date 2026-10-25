/*
 * Sci2Card: Triforce SCI2 (RS232C port #2) card reader link,
 * 0x8007660C..0x80076BBC. These functions and Sci2Card_Tick address one
 * string pool from its base, so the pool is defined here.
 */

extern "C" {
void *FUN_8003b120(unsigned int size);
void MemoryManager_Free(void *ptr);
void *memset(void *dst, int val, unsigned int n);
void *memcpy(void *dst, const void *src, unsigned int n);
void DebugPrintf(const char *fmt, ...);
int fn_80293860(unsigned char *rxBuf, unsigned short rxSize, unsigned char *txBuf,
                unsigned short txSize, void *port);
int fn_802937C8(int ch, int arg);
int fn_80293808(void);
int fn_80293338(int ch, unsigned char c);
int fn_80293290(int ch, int *count);
unsigned char fn_8029321C(int ch);

extern const double lbl_806D2EC0;
extern const double lbl_806D2EC8;
extern const char lbl_806D2ED0[5];
extern const char lbl_806D2ED8[5];
extern const char lbl_806D2EE0[4];
extern const char lbl_806D2EE4[7];
extern const char lbl_806D2EEC[8];

extern const char lbl_803114D0[19] = "USE RS232C PORT#2\n";
extern const char lbl_803114E4[17] = "  DATA BITS: %d\n";
extern const char lbl_803114F8[14] = "  PARITY: %s\n";
extern const char lbl_80311508[17] = "  STOP BITS: %d\n";
extern const char lbl_8031151C[11] = "  CTS: %s\n";
extern const char lbl_80311528[13] = "  SPEED: %d\n";
extern const char lbl_80311538[12] = "  SEND: %d\n";
extern const char lbl_80311544[12] = "  RECV: %d\n";
extern const char lbl_80311550[50] = "clTriforceSci2Device::open::acSciPortInit2 error\n";
extern const char lbl_80311584[19] = "warning send size\n";
extern const char lbl_80311598[11] = "sci2 open\n";
extern const char lbl_803115A4[12] = "sci2 close\n";
extern const char lbl_803115B0[13] = "no open sci\n";
extern const char lbl_803115C0[22] = "sci send error.empty\n";
extern const char lbl_803115D8[22] = "sci send other error\n";
}

class Sci2Port {
public:
    inline Sci2Port()
    {
        memset(this, 0, 6);
        m_parityOdd = 0;
        m_parityOn = 0;
        m_stop2 = 0;
        m_dataBits = 3;
        m_cts = 1;
        m_b4 = lbl_806D2EC0;
        m_b5 = lbl_806D2EC8;
        m_txSize = 0x400;
        m_txBuf = (unsigned char *)FUN_8003b120(m_txSize);
        memset(m_txBuf, 0, m_txSize);
        m_rxSize = 0x400;
        m_rxBuf = (unsigned char *)FUN_8003b120(m_rxSize);
        memset(m_rxBuf, 0, m_rxSize);
        DebugPrintf(lbl_803114D0);
        DebugPrintf(lbl_803114E4, m_dataBits + 5);
        DebugPrintf(lbl_803114F8, !m_parityOn ? lbl_806D2ED0 : (!m_parityOdd ? lbl_806D2ED8 : lbl_806D2EE0));
        DebugPrintf(lbl_80311508, (m_stop2 == 0) ? 1 : 2);
        DebugPrintf(lbl_8031151C, !m_cts ? lbl_806D2EE4 : lbl_806D2EEC);
        DebugPrintf(lbl_80311528, 9600);
        DebugPrintf(lbl_80311538, m_txSize);
        DebugPrintf(lbl_80311544, m_rxSize);
        m_open = 0;
    }

    inline void Open()
    {
        if (m_open != 1) {
            if (fn_80293860(m_rxBuf, m_rxSize, m_txBuf, m_txSize, this) == 1) {
                DebugPrintf(lbl_80311550);
            } else {
                if (fn_802937C8(1, 0x52) != 0) {
                    DebugPrintf(lbl_80311584);
                }
                m_open = 1;
                DebugPrintf(lbl_80311598);
            }
        }
    }

    inline void Close()
    {
        if (m_open != 0) {
            if (fn_80293808() != 1) {
                m_open = 0;
                DebugPrintf(lbl_803115A4);
            }
        }
    }

    inline ~Sci2Port()
    {
        if (m_open == 1) {
            Close();
            m_open = 0;
        }
        MemoryManager_Free(m_txBuf);
        m_txBuf = 0;
        MemoryManager_Free(m_rxBuf);
        m_rxBuf = 0;
    }

    unsigned char m_b0;
    unsigned char m_pad1 : 3;
    unsigned char m_parityOdd : 1;
    unsigned char m_parityOn : 1;
    unsigned char m_stop2 : 1;
    unsigned char m_dataBits : 2;
    unsigned char m_cts : 1;
    unsigned char m_pad2 : 7;
    unsigned char m_b3;
    unsigned char m_b4;
    unsigned char m_b5;
    unsigned char m_open;
    unsigned char m_pad07;
    unsigned char *m_txBuf;
    int m_txSize;
    unsigned char *m_rxBuf;
    int m_rxSize;
};

class Sci2Card {
public:
    Sci2Card();

    inline void ClearRx()
    {
        m_status[0] = 0;
        m_status[1] = 0;
        m_status[2] = 0;
        memset(m_rxBuf, 0, 0x102);
        m_rxLen = 0;
    }

    inline void SetState(int state)
    {
        m_state = state;
        m_unk20 = 0;
        m_unk24 = 120;
    }

    inline void Retry(int state)
    {
        m_state = state;
        m_retry--;
        m_unk20 = 0;
        m_unk24 = 120;
    }

    inline int SendByte(unsigned char c)
    {
        if (m_port->m_open == 0) {
            DebugPrintf(lbl_803115B0);
            return 2;
        }
        switch (fn_80293338(1, c)) {
        case 0:
            return 0;
        case 2:
            DebugPrintf(lbl_803115C0);
            return 1;
        case 1:
        default:
            DebugPrintf(lbl_803115D8);
            return 4;
        }
    }

    inline void SendBuffer(unsigned char *data, int len)
    {
        if (data == 0) {
            data = m_txBuf;
            len = m_txLen;
        }
        SendRaw(len, data);
    }

    inline void SendRaw(int n, unsigned char *p)
    {
        while (n > 0) {
            if (SendByte(*p) == 0) {
                p++;
                n--;
            }
        }
    }

    inline int Available(int *count)
    {
        if (m_port->m_open == 0) {
            return 2;
        }
        if (count == 0) {
            return 3;
        }
        if (fn_80293290(1, count) == 0) {
            return 0;
        }
        return 4;
    }

    inline int RecvByte(unsigned char *c)
    {
        int count;
        if (fn_80293290(1, &count) == 0) {
            if (count <= 0) {
                return 5;
            }
            *c = fn_8029321C(1);
            return 0;
        }
        return 1;
    }

    inline void SetStatus(unsigned char a, unsigned char b, unsigned char c)
    {
        m_status[0] = a;
        m_status[1] = b;
        m_status[2] = c;
    }

    inline int CheckFrame(unsigned char *rx, int rxLen)
    {
        int len;
        unsigned char *q;
        int sum;
        int i;

        if (rxLen < 2) {
            return 1;
        }
        len = rx[1];
        if (rxLen != len + 2) {
            return 1;
        }
        sum = len;
        q = rx + 2;
        for (i = len - 1; i > 0; i--) {
            sum ^= *q++;
        }
        if ((unsigned char)sum != rx[len + 1]) {
            return 3;
        }
        return 2;
    }

    inline int Receive()
    {
        int count;
        unsigned char c;
        unsigned char *rx;
        int r;
        unsigned char *q;
        int sum;
        int len;
        int i;

        if (Available(&count) == 0 && count > 0) {
            while (RecvByte(&c) == 0) {
                m_rxBuf[m_rxLen] = c;
                m_rxLen++;
                if (m_rxLen > 0x102) {
                    return 3;
                }
                rx = m_rxBuf;
                if (m_rxLen < 2) {
                    r = 1;
                } else {
                    len = rx[1];
                    if (m_rxLen != len + 2) {
                        r = 1;
                    } else {
                        sum = len;
                        q = rx + 2;
                        for (i = len - 1; i > 0; i--) {
                            sum ^= *q++;
                        }
                        if ((unsigned char)sum != rx[len + 1]) {
                            r = 3;
                        } else {
                            r = 2;
                        }
                    }
                }
                if (r == 3) {
                    return 3;
                }
                if (r == 2) {
                    SetStatus(rx[3], rx[4], rx[5]);
                    return 2;
                }
                if (count <= 1) {
                    return 1;
                }
            }
        }
        return 0;
    }

    int m_state;
    unsigned char m_status[4];
    unsigned char *m_txBuf;
    int m_txLen;
    unsigned char *m_rxBuf;
    int m_rxLen;
    Sci2Port *m_port;
    int m_retry;
    int m_unk20;
    int m_unk24;
};

extern "C" void Sci2Card_AllocAndOpenSci2(Sci2Card *card)
{
    Sci2Port *port;
    card->m_port = new Sci2Port;
    port = card->m_port;
    port->Open();
}

#pragma dont_inline on
Sci2Card::Sci2Card()
{
    Sci2Card_AllocAndOpenSci2(this);
    m_txBuf = 0;
    m_rxBuf = 0;
    m_retry = 8;
    MemoryManager_Free(m_txBuf);
    m_txBuf = (unsigned char *)FUN_8003b120(0x102);
    memset(m_txBuf, 0, 0x102);
    MemoryManager_Free(m_rxBuf);
    m_rxBuf = (unsigned char *)FUN_8003b120(0x102);
    memset(m_rxBuf, 0, 0x102);
    m_rxLen = 0;
    m_state = 0;
    m_unk20 = 0;
    m_unk24 = 0;
}
#pragma dont_inline reset

/*
 * Frame: type, length, sub-command, three zero bytes, payload, ETX (3),
 * then an XOR checksum over the length byte through the ETX.
 */
extern "C" unsigned char Sci2Card_BuildPacket(void *card, unsigned char *buf, int *outLen,
                                              unsigned char frameType, unsigned char subCmd,
                                              unsigned char *data, int dataLen)
{
    unsigned char *p;
    unsigned char *q;
    int sum;
    int i;

    if (data == 0 && dataLen > 0) {
        return 0;
    }
    if (data != 0 && dataLen <= 0) {
        return 0;
    }
    if (dataLen > 0xFF) {
        return 0;
    }
    buf[0] = frameType;
    buf[1] = 6;
    buf[1] += (unsigned char)dataLen;
    buf[2] = subCmd;
    buf[3] = 0;
    buf[4] = 0;
    buf[5] = 0;
    p = buf + 6;
    if (dataLen > 0) {
        memcpy(p, data, dataLen);
        p += dataLen;
    }
    *p = 3;
    q = buf + 2;
    sum = buf[1];
    for (i = dataLen + 5; i > 0; i--) {
        sum ^= *q++;
    }
    p[1] = sum;
    *outLen = dataLen + 8;
    return 1;
}

/* The singleton pointer lives in .sdata2. Declaring it const (and writing
 * through a cast) gives the load scheduling and no-reload-after-store
 * behaviour of the original code. */
extern "C" Sci2Card *const lbl_806D2EB8;
#define s_card (*(Sci2Card **)&lbl_806D2EB8)

extern "C" void Sci2Card_Shutdown(void)
{
    if (s_card != 0) {
        if (s_card != 0) {
            delete s_card->m_port;
            s_card->m_port = 0;
            MemoryManager_Free(s_card->m_txBuf);
            s_card->m_txBuf = 0;
            MemoryManager_Free(s_card->m_rxBuf);
            s_card->m_rxBuf = 0;
            operator delete(s_card);
        }
        s_card = 0;
    }
}

#pragma dont_inline on
extern "C" Sci2Card *Sci2Card_Singleton_GetOrCreate(void)
{
    if (s_card == 0) {
        s_card = new Sci2Card();
    }
    return s_card;
}
#pragma dont_inline reset

extern "C" Sci2Card *Sci2Card_Singleton_Get(void)
{
    return s_card;
}
