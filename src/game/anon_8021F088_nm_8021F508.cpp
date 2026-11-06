#include "game/anon_8021F088_nm_8021F508_private.h"


void ItemWnd::Setup(int n, MilageItem *e) {
    const SetupPool *pool = &lbl_803C6610;
    if (e != 0) {
        coins = n;
        entry = e;
        state = 1;
        timer = 0;
        sub = 0;
        if (e->type == 1) {
            itemId = fn_8021620C();
            if (itemId <= 0) {
                DebugPrintf((const char *)pool + 0x670, (const char *)pool + 0x694, 950);
                state = 0;
                return;
            }
            KartPose *pose = fn_8013BE98();
            if (kart) {
                delete kart;
                kart = 0;
            }
            kart = new Model(ItemRes_LookupByKey_Thunk(itemId), 1);
            fn_8013D738(kart, lbl_806DB190, lbl_806DB194);
            fn_8013D660(kart, lbl_806DB1CC, lbl_806DB1D0);
            fn_8013D634(kart, lbl_806DB1D4 * pose->pos[0], lbl_806DB1D4 * pose->pos[1], lbl_806DB1D4 * pose->pos[2]);
            fn_8013D59C(kart, lbl_806DB1D8 * pose->rot[0], lbl_806DB1D8 * pose->rot[1], lbl_806DB1D8 * pose->rot[2]);
            float s = lbl_806DB1D4 * pose->scale;
            fn_8013D608(kart, s, s, s);
            TextSprite tmp;
            tmp.visible = 0;
            TexMgr_SetTexture(&tmp, fn_8023DAA8(itemId));
            TexMgr_Apply(&tmp);
            TexMgr_SetTexture(&tmp, fn_8023D938(itemId, 0));
            TexMgr_Apply(&tmp);
            TexMgr_SetTexture(&tmp, fn_8023D938(itemId, 1));
            TexMgr_Apply(&tmp);
            TexMgr_SetTexture(&tmp, fn_8023D938(itemId, 2));
            TexMgr_Apply(&tmp);
        } else if (e->type == 3 || e->type == 4) {
            int k = fn_80216960(entry->id);
            if (item) {
                delete item;
                item = 0;
            }
            item = new ItemModel(k, 2, 0, 1);
            fn_8021A7BC(item, pool->poses[k].x, pool->poses[k].y);
            fn_8021A578(item, lbl_806DB1D8 * pool->poses[k].rot[0], lbl_806DB1D8 * pool->poses[k].rot[1],
                        lbl_806DB1D8 * pool->poses[k].rot[2]);
            fn_8021A660(item, pool->poses[k].scale, pool->poses[k].scale, pool->poses[k].scale);
            fn_8021A430(item, lbl_806DB190);
        }
    }
}

