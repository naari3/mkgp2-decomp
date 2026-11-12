#include "game/types/Node.h"

extern "C" void fn_8016E7E4(Node *n, Node *item) {
    if (n->next != 0) {
        fn_8016E7E4(n->next, item);
    } else {
        n->next = item;
    }
}

#include "game/types/clKPCharaData.h"
extern "C" {
extern const float lbl_806D8BAC;
extern const float lbl_806D8BB0;
extern const float lbl_806D8BA8;

}

void clKPCharaData_MKoopa::Update() {
    float t = frame + lbl_806D8BAC;
    frame = t;
    if (t > lbl_806D8BB0) {
        frame = lbl_806D8BA8;
    }
}
