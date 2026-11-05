struct Node {
    Node *next;
    ~Node() { if (next) delete next; }
};
struct Model { ~Model(); };
struct Group {
    Group *next;
    Model *model;
    Node *items;
    ~Group();
};
Group::~Group() {
    if (next) delete next;
    if (items) delete items;
    if (model) delete model;
}
