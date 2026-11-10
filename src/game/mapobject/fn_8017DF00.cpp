#include "game/mapobject/mapobject17b_debug_private.h"

static inline void MapDebugEditOrPrint(const char *base, MapDebugInput *input, unsigned char left) {
    Vec3f *point;
    clPathNode *sel;
    clPathNode *node;
    int i;
    if (left) {
        if (lbl_806D163C) {
                DebugPrintf(base + 0x8C0);
                DebugPrintf(base + 0x8F8);
                node = lbl_806D163C;
                while (node) {
                    DebugPrintf(lbl_806D9194);
                    for (i = 0, point = node->points; i < 4; i++, point++) {
                        DebugPrintf(base + 0x91C, point->x, point->y, point->z);
                    }
                    DebugPrintf(base + 0x934);
                    DebugPrintf(lbl_806D919C);
                    node = node->next;
                }
                DebugPrintf(lbl_806D91A4);
                DebugPrintf(base + 0x8C0);
        }
    } else {
            sel = lbl_806D1640;
            if (input->Pressed(2)) {
                if (sel) {
                    sel->index++;
                    if (sel->index > 3) sel->index = 0;
                    lbl_80677D00.x = sel->points[sel->index].x;
                    lbl_80677D00.z = sel->points[sel->index].z;
                }
            } else if (input->Held(1)) {
                if (sel) {
                    float axis = input->AxisX();
                    if (axis > lbl_806D9188 || axis < lbl_806D918C) {
                        sel->points[sel->index].x += lbl_806D91A8 * (lbl_806D9190 * axis);
                    }
                    axis = input->AxisY();
                    if (axis > lbl_806D9188 || axis < lbl_806D918C) {
                        sel->points[sel->index].z -= lbl_806D91A8 * (lbl_806D9190 * axis);
                    }
                }
            } else MapDebugMoveCamera(input);
    }
}

extern "C" void fn_8017DF00() {
    const char *base = lbl_80376220;
    if (lbl_806D1618 == 0 || lbl_806D1620 == 0) return;
    unsigned char right;
    unsigned char left;
    right = 0;
    left = 0;
    MapDebugInput *input = InputMgr_GetPlayer(GetInputManager(), 0);
    if (input->Right() > lbl_806D9188) {
        if (lbl_806D1634 == 0) right = 1;
        lbl_806D1634++;
    } else lbl_806D1634 = 0;
    if (input->Left() > lbl_806D9188) {
        if (lbl_806D1638 == 0) left = 1;
        lbl_806D1638++;
    } else lbl_806D1638 = 0;
    if (lbl_806D1628 == 0) return;
    if (lbl_806D1628 == 1) {
        if (input->Pressed(8)) lbl_806CFB84 = !lbl_806CFB84;
        MapDebugMoveCamera(input);
        float amount = input->Right();
        if (amount > lbl_806D9188) {
            Vec3f delta;
            delta.x = lbl_80677D0C.x * amount;
            delta.y = lbl_80677D0C.y * amount;
            delta.z = lbl_80677D0C.z * amount;
            lbl_80677D00.x += lbl_806D9190 * delta.x;
            lbl_80677D00.y += lbl_806D9190 * delta.y;
            lbl_80677D00.z += lbl_806D9190 * delta.z;
        }
        amount = input->Left();
        if (amount > lbl_806D9188) {
            Vec3f delta;
            delta.x = lbl_80677D0C.x * amount;
            delta.y = lbl_80677D0C.y * amount;
            delta.z = lbl_80677D0C.z * amount;
            lbl_80677D00.x -= lbl_806D9190 * delta.x;
            lbl_80677D00.y -= lbl_806D9190 * delta.y;
            lbl_80677D00.z -= lbl_806D9190 * delta.z;
        }
    } else if (lbl_806D1628 == 2) {
        if (input->Pressed(8)) {
            if (fn_8017E6A8()) {
                clPathNode *node = lbl_806D1640;
                node->points[0].x = lbl_80677D00.x;
                node->points[0].z = lbl_80677D00.z;
                node->points[1].x = lbl_80677D00.x;
                node->points[1].z = lbl_80677D00.z;
                node->points[2].x = lbl_80677D00.x;
                node->points[2].z = lbl_80677D00.z;
                node->points[3].x = lbl_80677D00.x;
                node->points[3].z = lbl_80677D00.z;
            }
        } else if (input->Pressed(4)) {
            MapDebugRemoveNode(lbl_806D1640);
            MapDebugSelectStart();
        } else if (right) {
            if (lbl_806D1640) {
                if (lbl_806D1640->next == 0) lbl_806D1640 = lbl_806D163C;
                else lbl_806D1640 = lbl_806D1640->next;
            }
            MapDebugSelectStart();
        } else {
            MapDebugEditOrPrint(base, input, left);
        }
    }
    void *camera = lbl_806D1618->cobj;
    if (camera) {
        Vec3f interest;
        interest.x = lbl_806D91AC * lbl_80677D0C.x + lbl_80677D00.x;
        interest.y = lbl_806D91AC * lbl_80677D0C.y + lbl_80677D00.y;
        interest.z = lbl_806D91AC * lbl_80677D0C.z + lbl_80677D00.z;
        HSD_CObjSetEyePosition(camera, &lbl_80677D00);
        HSD_CObjSetInterest(camera, &interest);
    }
}
