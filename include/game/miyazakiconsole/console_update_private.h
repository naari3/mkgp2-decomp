#ifndef MIYAZAKI17E_CONSOLE_UPDATE_PRIVATE_H
#define MIYAZAKI17E_CONSOLE_UPDATE_PRIVATE_H
struct ConsoleInput {
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual bool IsTriggered(int);
    virtual bool IsHeld(int);
};
struct ConsolePage {
    virtual void slot08();
    virtual void Release();
    virtual void Update();
    unsigned char closed;
};

#endif
