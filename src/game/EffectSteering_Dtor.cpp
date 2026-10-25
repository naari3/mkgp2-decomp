/* EffectSteering_Dtor and the steering action destructors, 0x8005C51C..0x8005CA64.
 * Same layout views as EffectSteeringCtor.cpp. The vtables live in .data and
 * are referenced through extab_user_renames.json.
 */
void operator delete(void *);
void operator delete[](void *);
struct ESCtor;

struct ESBase {
    virtual ~ESBase() {}
    virtual void Reset();
    virtual void Step();
};
struct ESScl : ESBase {
    ESCtor *owner; int field8;
    virtual void Reset();
    virtual ~ESScl();
};
struct ESSha : ESBase {
    ESCtor *owner; int field8, fieldC, field10, field14;
    unsigned char active; char pad19[3]; int field1C, field20;
    virtual void Reset();
    virtual ~ESSha();
};
struct ESSpl : ESBase {
    ESCtor *owner; char pad8[0x14];
    virtual void Reset();
    virtual ~ESSpl();
};
struct ESVis : ESBase {
    ESCtor *owner; char pad8[0xC];
    virtual void Reset();
    virtual ~ESVis();
};
struct ESVib : ESBase {
    ESCtor *owner; int field8, fieldC, field10, field14, field18, field1C;
    unsigned char active; char pad21[0xB];
    virtual void Reset();
    virtual ~ESVib();
};
struct ESLck : ESBase {
    ESCtor *owner; char pad8[0x14];
    virtual void Reset();
    virtual ~ESLck();
};
struct ESRng : ESBase {
    ESCtor *owner; int field8;
    virtual void Reset();
    virtual ~ESRng();
};
struct ESSamples {
    int count; float *samples;
    ~ESSamples() { delete[] samples; samples = 0; }
};
struct ESDly : ESBase {
    ESCtor *owner; ESSamples buf;
    int readIndex, writeIndex, remaining, field1C;
    virtual void Reset();
    virtual ~ESDly();
};

template <class T> struct ESOwn {
    T *p;
    ~ESOwn() throw() { delete p; }
};

struct ESListener {
    virtual void f0();
    virtual void Release();
};

struct ESCtor {
    void *owner; unsigned char mode; char pad5[3];
    int field8, fieldC, field10, field14;
    unsigned char active; char pad19[3]; int field1C; ESListener *listener;
    ESOwn<ESScl> scale; ESOwn<ESSha> shake; ESOwn<ESSpl> split; ESOwn<ESVis> viscosity;
    ESOwn<ESVib> vibrate; ESOwn<ESLck> lock; ESOwn<ESRng> range; ESOwn<ESDly> delay;
    float value;
    ~ESCtor();
};

ESCtor::~ESCtor()
{
    if (field1C != 0) {
        listener->Release();
    }
}

ESScl::~ESScl() {}
ESSha::~ESSha() {}
ESSpl::~ESSpl() {}
ESVis::~ESVis() {}
ESVib::~ESVib() {}
ESLck::~ESLck() {}
ESRng::~ESRng() {}
ESDly::~ESDly() {}
