extern unsigned int OSGetTick(void);

extern unsigned int lbl_806D1140;
extern unsigned int lbl_806D1144;

void DVDLoad_RecordOpStart(unsigned int offset)
{
    lbl_806D1140 = offset >> 10;
    lbl_806D1144 = OSGetTick();
}
