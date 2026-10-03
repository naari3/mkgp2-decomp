/* EffectSteering_Ctor @ 8005CA64..8005CCBC.
 * Local observed-layout views, not a verified full runtime class definition.
 * Target and cleanup callees reconstructed from complete original assembly.
 */
void *operator new(unsigned long);
void *operator new[](unsigned long);
void operator delete(void *);
struct ESCtor;

struct ESBase {
    ESBase() {}
    virtual ~ESBase();
};
struct ESScl : ESBase {
    ESCtor *owner; int field8;
    ESScl(ESCtor *p) : owner(p) {}
    virtual ~ESScl();
};
struct ESSha : ESBase {
    ESCtor *owner; int field8, fieldC, field10, field14;
    unsigned char active; char pad19[3]; int field1C, field20;
    ESSha(ESCtor *p) : owner(p), field8(0), fieldC(0), field14(0), active(0) {}
    virtual ~ESSha();
};
struct ESSpl : ESBase {
    ESCtor *owner; char pad8[0x14];
    ESSpl(ESCtor *p) : owner(p) {}
    virtual ~ESSpl();
};
struct ESVis : ESBase {
    ESCtor *owner; char pad8[0xC];
    ESVis(ESCtor *p) : owner(p) {}
    virtual ~ESVis();
};
struct ESVib : ESBase {
    ESCtor *owner; int field8, fieldC, field10, field14, field18, field1C;
    unsigned char active; char pad21[0xB];
    ESVib(ESCtor *p) : owner(p), field10(0), field14(0), field1C(0), active(0) {}
    virtual ~ESVib();
};
struct ESLck : ESBase {
    ESCtor *owner; char pad8[0x14];
    ESLck(ESCtor *p) : owner(p) {}
    virtual ~ESLck();
};
struct ESRng : ESBase {
    ESCtor *owner; int field8;
    ESRng(ESCtor *p) : owner(p) {}
    virtual ~ESRng();
};
struct ESDly : ESBase {
    ESCtor *owner; int count; float *samples;
    int readIndex, writeIndex, remaining, field1C;
    ESDly(ESCtor *p, int n) : owner(p), count(n) {
        if (count < 3) count = 3;
        count++;
        samples = 0;
        samples = new float[count];
        readIndex = 0;
        writeIndex = 0;
        remaining = 0;
    }
    virtual ~ESDly();
};

/* Seven distinct owning subobjects have seven external cleanup destructors.
 * The constructor initializers generate DESTROYMEMBER actions naturally.
 */
struct ESOwn1 { ESScl *p; ESOwn1(ESCtor *s) : p(new ESScl(s)) {} ~ESOwn1() throw(); };
struct ESOwn2 { ESSha *p; ESOwn2(ESCtor *s) : p(new ESSha(s)) {} ~ESOwn2() throw(); };
struct ESOwn3 { ESSpl *p; ESOwn3(ESCtor *s) : p(new ESSpl(s)) {} ~ESOwn3() throw(); };
struct ESOwn4 { ESVis *p; ESOwn4(ESCtor *s) : p(new ESVis(s)) {} ~ESOwn4() throw(); };
struct ESOwn5 { ESVib *p; ESOwn5(ESCtor *s) : p(new ESVib(s)) {} ~ESOwn5() throw(); };
struct ESOwn6 { ESLck *p; ESOwn6(ESCtor *s) : p(new ESLck(s)) {} ~ESOwn6() throw(); };
struct ESOwn7 { ESRng *p; ESOwn7(ESCtor *s) : p(new ESRng(s)) {} ~ESOwn7() throw(); };

extern "C" const float lbl_806D297C;
struct ESCtor {
    void *owner; unsigned char mode; char pad5[3];
    int field8, fieldC, field10, field14;
    unsigned char active; char pad19[3]; int field1C, field20;
    ESOwn1 scale; ESOwn2 shake; ESOwn3 split; ESOwn4 viscosity;
    ESOwn5 vibrate; ESOwn6 lock; ESOwn7 range;
    ESDly *delay; float value;
    ESCtor(void *, unsigned char);
};

ESCtor::ESCtor(void *p, unsigned char m)
    : owner(p), mode(m), field8(0), fieldC(0), field14(0), active(0),
      field1C(0), field20(0), scale(this), shake(this), split(this),
      viscosity(this), vibrate(this), lock(this), range(this)
{
    delay = new ESDly(this, 13);
    value = lbl_806D297C;
}
