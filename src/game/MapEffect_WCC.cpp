/*
 * 0x801755BC..0x801759D8: the Wario Colosseum secret-cup map effect. It
 * keeps a linked list of effect parts (a sound effect part and a texture
 * scroller over the course's moving-texture joints); the list append is
 * recursive.
 * Real C++ for the inline constructors; mangled names are bridged in
 * tools/extab_user_renames.json.
 */

struct JObj;

extern "C" {
extern const char lbl_80371AE8[];
void DebugPrintf(const char *, ...);
JObj *ResolveJointByName(JObj *, const char *);
}

struct MoveTexDesc {
    const char *name;
    int pad04;
    float speed;
};

extern "C" {
extern MoveTexDesc lbl_80370E58[];
}

struct clMapEffectParts {
    virtual void vKeyFunction();
    virtual ~clMapEffectParts();
    clMapEffectParts() {}
};

struct clSoundParts : clMapEffectParts {
    char pad04[0x20];

    clSoundParts();
};

struct clMoveTex : clMapEffectParts {
    MoveTexDesc *table;
    JObj **joints;
    int count;

    virtual void vKeyFunction2();

    clMoveTex(JObj *root) {
        DebugPrintf(lbl_80371AE8);
        table = lbl_80370E58;
        joints = 0;
        count = 0;
        if (table && root) {
            for (;;) {
                if (!table[count].name) {
                    break;
                }
                count++;
            }
            if (count) {
                int i;

                joints = new JObj *[count];
                for (i = 0; i < count; i++) {
                    joints[i] = ResolveJointByName(root, table[i].name);
                }
            }
        }
    }
};

struct PartsNode {
    int kind;
    int prio;
    clMapEffectParts *parts;
    unsigned char done;
    PartsNode *next;

    PartsNode(int kind, int prio, clMapEffectParts *parts) {
        this->kind = kind;
        this->prio = prio;
        this->parts = parts;
        done = 0;
        next = 0;
    }

    int Append(int kind, int prio, clMapEffectParts *parts) {
        if (parts) {
            if (next) {
                next->Append(kind, prio, parts);
            } else {
                next = new PartsNode(kind, prio, parts);
            }
            return 1;
        }
        return 0;
    }
};

struct PartsList {
    PartsNode *head;

    PartsList() {
        head = 0;
    }

    int Add(int kind, int prio, clMapEffectParts *parts);
};

struct clMapEffect {
    virtual ~clMapEffect();
    virtual void Update();
    virtual void Draw();

    clMapEffect() {}
};

struct clMapEffectWCC : clMapEffect {
    PartsList *parts;
    unsigned char done;

    virtual void vKeyFunction();

    clMapEffectWCC(JObj *root, int arg);
};

#pragma exceptions on

clMapEffectWCC::clMapEffectWCC(JObj *root, int arg) {
    parts = 0;
    done = 0;
    parts = new PartsList();
    if (parts) {
        parts->Add(4, 2, new clSoundParts());
        parts->Add(0, 0, new clMoveTex(root));
    }
}

int PartsList::Add(int kind, int prio, clMapEffectParts *parts) {
    if (!parts) {
        return 0;
    }
    if (head) {
        head->Append(kind, prio, parts);
    } else {
        head = new PartsNode(kind, prio, parts);
    }
    return 1;
}

#pragma exceptions reset
