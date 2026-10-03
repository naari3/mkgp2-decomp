/* The observed lifetime view has only the vptr at offset zero. */
void operator delete(void *);

class JvsInputLifetime {
public:
    /* An external key method leaves the existing vtable in its owning TU. */
    virtual void KeyFunction();
    virtual ~JvsInputLifetime();
};

JvsInputLifetime::~JvsInputLifetime()
{
}
