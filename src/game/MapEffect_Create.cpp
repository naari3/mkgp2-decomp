/*
 * 0x801752C0..0x801755BC: creates the map effect for the current cup. Most
 * cups construct their own clMapEffect subclass; the three secret cups that
 * need no joints use small inline classes (one also resets the fog).
 * Real C++ for the inline constructors; mangled names are bridged in
 * tools/extab_user_renames.json.
 */

struct JObj;

extern "C" {
extern int g_cupId;
void fn_8016B248(void *desc);
void fn_8016B178(int mode);
void fn_8016B160(float v);
void fn_8016B148(float v);
void fn_8016B0F0(unsigned char r, unsigned char g, unsigned char b);
}

struct clMapEffect {
    virtual ~clMapEffect();
    virtual void Update();
    virtual void Draw();

    clMapEffect() {}
};

struct clMapEffectMR : clMapEffect {
    char pad04[0x8];

    clMapEffectMR(JObj *root, int arg);
};

struct clMapEffectDK : clMapEffect {
    char pad04[0x14];

    clMapEffectDK(JObj *root, int arg);
};

struct clMapEffectWC : clMapEffect {
    char pad04[0x8];

    clMapEffectWC(JObj *root, int arg);
};

struct clMapEffectPC : clMapEffect {
    char pad04[0xC];

    clMapEffectPC(JObj *root, int arg);
};

struct clMapEffectKP : clMapEffect {
    char pad04[0x2C];

    clMapEffectKP(JObj *root, int arg);
};

struct clMapEffectRB : clMapEffect {
    char pad04[0xC];

    clMapEffectRB(JObj *root, int arg);
};

struct clMapEffectYI : clMapEffect {
    char pad04[0x8];

    clMapEffectYI(JObj *root, int arg);
};

struct clMapEffectDN : clMapEffect {
    char pad04[0x8];

    clMapEffectDN(JObj *root, int arg);
};

struct clMapEffectWCC : clMapEffect {
    char pad04[0x8];

    clMapEffectWCC(JObj *root, int arg);
};

struct clMapEffectDKC : clMapEffect {
    int a;
    int b;
    int c;
    unsigned char d;

    virtual ~clMapEffectDKC();
    virtual void Update();
    virtual void Draw();

    clMapEffectDKC() {
        a = 0;
        b = 0;
        c = 0;
        d = 0;
        fn_8016B248(0);
        fn_8016B178(2);
        fn_8016B160(0.0f);
        fn_8016B148(10000.0f);
        fn_8016B0F0(0xC0, 0xC0, 0xC0);
    }
};

struct clMapEffectPCC : clMapEffect {
    unsigned char done;

    virtual ~clMapEffectPCC();
    virtual void Update();
    virtual void Draw();

    clMapEffectPCC() {
        done = 0;
    }
};

struct clMapEffectKPC : clMapEffect {
    unsigned char done;

    virtual ~clMapEffectKPC();
    virtual void Update();
    virtual void Draw();

    clMapEffectKPC() {
        done = 0;
    }
};

#pragma exceptions on

extern "C" clMapEffect *fn_801752C0(JObj *root, int arg) {
    if (!root) {
        return 0;
    }
    switch (g_cupId) {
    case 1:
        return new clMapEffectMR(root, arg);
    case 2:
        return new clMapEffectDK(root, arg);
    case 3:
        return new clMapEffectWC(root, arg);
    case 4:
        return new clMapEffectPC(root, arg);
    case 5:
        return new clMapEffectKP(root, arg);
    case 6:
        return new clMapEffectRB(root, arg);
    case 7:
        return new clMapEffectYI(root, arg);
    case 8:
        return new clMapEffectDN(root, arg);
    case 10:
        return new clMapEffectDKC();
    case 11:
        return new clMapEffectWCC(root, arg);
    case 12:
        return new clMapEffectPCC();
    case 13:
        return new clMapEffectKPC();
    case 14:
        return new clMapEffectRB(root, arg);
    case 15:
        return new clMapEffectYI(root, arg);
    case 16:
        return new clMapEffectDN(root, arg);
    }
    return 0;
}

#pragma exceptions reset
