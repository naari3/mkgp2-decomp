/*
 * Sci2Card singleton teardown and lazy creation, 0x80076A80..0x80076BB4.
 */

extern "C" {
void MemoryManager_Free(void *ptr);
void DebugPrintf(const char *fmt, ...);
int fn_80293808(void);
extern const char lbl_803115A4[];
}

class Sci2Port {
public:
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

    unsigned char m_flags[6];
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

extern "C" Sci2Card *Sci2Card_Singleton_GetOrCreate(void)
{
    if (s_card == 0) {
        s_card = new Sci2Card();
    }
    return s_card;
}
