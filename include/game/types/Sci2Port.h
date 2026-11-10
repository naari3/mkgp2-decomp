#ifndef GAME_TYPES_SCI2PORT_H
#define GAME_TYPES_SCI2PORT_H

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

#endif /* GAME_TYPES_SCI2PORT_H */
