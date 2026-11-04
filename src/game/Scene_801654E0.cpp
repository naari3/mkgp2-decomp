#include "game/Scene_801654E0Private.h"

Obj801654E0::Obj801654E0(unsigned int id, unsigned int value) {
    fn_80121210();
    active = 0;
    panel = 0;
    kind = id;
    switch (kind) {
    case 0:
        panel = new DebugFirst163(0, 0);
        break;
    case 1:
        TaRecord_InsertResult(g_playerData, 0, 0, 0, g_characterId, lbl_806D8918);
        panel = new DebugRecord163(0, 0);
        break;
    case 2:
        if (!value) panel = new DebugCup163(0, 0, 1, 0);
        else {
            int count = fn_801D5C88(g_playerData, g_ccClass) == 1 ? 10 : 5;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 8; j++) {
                    if ((unsigned int)j < value) g_playerData[0x1ba + i * 8 + j] = count;
                    else g_playerData[0x1ba + i * 8 + j] = 1;
                }
            }
        }
        break;
    case 3: panel = new DebugTitle163; break;
    case 4: panel = new DebugName163; break;
    case 5: panel = new DebugTable163; break;
    case 6: panel = new DebugOther163; break;
    case 7:
        SetCourseParams(value + 1, 0, 0, 0);
        panel = new DebugModelPage163(0);
        break;
    case 8: panel = new DebugModelPage163(1); break;
    case 9: panel = new DebugModelPage163(2); break;
    case 10: panel = new DebugModelPage163(3); break;
    case 11: panel = new DebugRecord163(0, 0); break;
    default:
        done = 1;
        return;
    }
}
