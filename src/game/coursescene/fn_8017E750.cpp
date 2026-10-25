struct clPathNode {
    char pad[0x34];
    clPathNode *next;
    void Append(clPathNode *n);
};

void clPathNode::Append(clPathNode *n) {
    if (next == 0) {
        next = n;
    } else {
        next->Append(n);
    }
}
