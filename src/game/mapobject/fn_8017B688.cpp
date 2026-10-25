struct clModelGroup {
    clModelGroup *next;
    void Append(clModelGroup *node);
};

void clModelGroup::Append(clModelGroup *node) {
    if (next) {
        next->Append(node);
    } else {
        next = node;
    }
}
