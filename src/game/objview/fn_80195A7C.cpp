struct Node {
    Node *next;
    ~Node();
};

Node::~Node() {
    if (next) {
        delete next;
    }
}
