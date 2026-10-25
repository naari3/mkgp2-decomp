/*
 * Sci2Card link state machine, 0x80076BBC..0x8007723C.
 * The string pool is defined in Sci2Card.cpp; the strings are addressed
 * from its base like the original code does. As one TU with the pool
 * (where CW keeps the pool base in r31) this was 98.9%; the residual is
 * the checksum loop counter copy and the enq pointer copy in state 3.
 */

extern "C" {
extern const char lbl_803114D0[];
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

}

#define lbl_803114E4 (lbl_803114D0 + 0x14)
#define lbl_803114F8 (lbl_803114D0 + 0x28)
#define lbl_80311508 (lbl_803114D0 + 0x38)
#define lbl_8031151C (lbl_803114D0 + 0x4C)
#define lbl_80311528 (lbl_803114D0 + 0x58)
#define lbl_80311538 (lbl_803114D0 + 0x68)
#define lbl_80311544 (lbl_803114D0 + 0x74)
#define lbl_80311550 (lbl_803114D0 + 0x80)
#define lbl_80311584 (lbl_803114D0 + 0xB4)
#define lbl_80311598 (lbl_803114D0 + 0xC8)
#define lbl_803115A4 (lbl_803114D0 + 0xD4)
#define lbl_803115B0 (lbl_803114D0 + 0xE0)
#define lbl_803115C0 (lbl_803114D0 + 0xF0)
#define lbl_803115D8 (lbl_803114D0 + 0x108)

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

extern "C" void Sci2Card_Tick(Sci2Card *card)
{
    unsigned char c;
    unsigned char enq;
    int r;

    if (card->m_state == 0 || card->m_state == 5) {
        return;
    }
    if (card->m_retry < 0) {
        return;
    }
    switch (card->m_state) {
    case 1:
        if (card->m_unk20-- > 0) {
            return;
        }
        card->ClearRx();
        card->SendBuffer(0, 0);
        card->SetState(2);
        break;
    case 2:
        if (card->RecvByte(&c) == 0) {
            if (c == 6) {
                card->SetState(3);
            } else {
                card->SetState(1);
                card->m_retry--;
            }
        } else {
            if (card->m_unk24-- > 0) {
                return;
            }
            card->Retry(1);
        }
        break;
    case 3:
        if (card->m_unk20-- > 0) {
            return;
        }
        card->ClearRx();
        enq = 5;
        card->SendBuffer(&enq, 1);
        card->SetState(4);
        break;
    case 4:
        r = card->Receive();
        if (r == 2) {
            if (!(card->m_status[1] == 0x30 && card->m_status[2] == 0x33)) {
                card->SetState(0);
            }
        } else if (r == 1) {
            if (card->m_unk24-- > 0) {
                return;
            }
            card->Retry(3);
        } else if (r == 3) {
            card->ClearRx();
            card->Retry(3);
        } else if (r == 0) {
            if (card->m_unk24-- > 0) {
                return;
            }
            card->Retry(3);
        }
        break;
    }
}
