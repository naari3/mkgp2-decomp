extern unsigned int OSGetTick(void);

extern unsigned int g_dvdLastReadPage;
extern unsigned int g_dvdLastReadTick;

void DVDLoad_RecordOpStart(unsigned int offset)
{
    g_dvdLastReadPage = offset >> 10;
    g_dvdLastReadTick = OSGetTick();
}
