/*
 * Sci2Card constructor, 0x80076870..0x80076910.
 */

extern "C" {
void *FUN_8003b120(unsigned int size);
void MemoryManager_Free(void *ptr);
void *memset(void *dst, int val, unsigned int n);
}

class Sci2Card;
extern "C" void Sci2Card_AllocAndOpenSci2(Sci2Card *card);

class Sci2Card {
public:
    Sci2Card();

    int m_state;
    unsigned char m_status[4];
    unsigned char *m_txBuf;
    int m_txLen;
    unsigned char *m_rxBuf;
    int m_rxLen;
    void *m_port;
    int m_retry;
    int m_unk20;
    int m_unk24;
};

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
