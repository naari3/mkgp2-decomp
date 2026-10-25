class Object {
public:
    ~Object();
};

class clModel {
public:
    clModel *next;
    char pad04[0x18];
    virtual void Update();
    virtual void Draw();
    ~clModel() {
        if (next) delete next;
    }
};

struct clModelGroup {
    clModelGroup *next;
    Object *obj;
    clModel *models;
    ~clModelGroup();
};

clModelGroup::~clModelGroup() {
    if (next) delete next;
    if (models) delete models;
    if (obj) delete obj;
}
