#include "game/types/Node.h"

void fn_8016E7E4(Node *n, Node *item) {
    if (n->next != 0) {
        fn_8016E7E4(n->next, item);
    } else {
        n->next = item;
    }
}
