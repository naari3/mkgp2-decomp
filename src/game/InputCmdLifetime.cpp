/* Observed layout only; the sample constructor belongs to another TU. */
void *operator new[](unsigned long);
void operator delete[](void *);
void operator delete(void *);
extern "C" void *lbl_806CEE50;

struct InputCmdOwnedSample {
    float x, y, z;
    int code;
    unsigned char live;
    unsigned char pad11[3];
    InputCmdOwnedSample();
};

struct InputCmdLifetime {
    unsigned char pad00[0x10];
    unsigned char mode;
    unsigned char pad11[3];
    void *config;
    int capacity;
    InputCmdOwnedSample *samples;
    int readIndex, writeIndex;
    unsigned char detected;
    unsigned char pad29[3];
    int cooldown;
    ~InputCmdLifetime();
    InputCmdLifetime(int);
};

InputCmdLifetime::~InputCmdLifetime()
{
    delete[] samples;
}

InputCmdLifetime::InputCmdLifetime(int count)
{
    mode = 0;
    config = lbl_806CEE50;
    capacity = count;
    samples = new InputCmdOwnedSample[capacity];
    readIndex = 0;
    writeIndex = 0;
    detected = 0;
    cooldown = 0;
}
