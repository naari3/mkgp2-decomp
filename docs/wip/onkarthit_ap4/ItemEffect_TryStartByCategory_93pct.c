#pragma exceptions off
typedef struct ItemActPair { int a, b; } ItemActPair;
int ItemEffect_TryStartByCategory(ItemStateBlock *self, int itemId, void *arg) { /* 0x80051304 size:0x344 */
    unsigned char *base = (unsigned char *)lbl_802EBA18;
    int idx;
    Vec3 vt; /* sp+0x14, tornado branch */
    Vec3 vg; /* sp+0x8, boss-grab branch */

    idx = ItemTable_FindEntryByIdStride20((ItemCatEntry20 *)(base + 0x1b9c), 0x1a, itemId);
    if (idx >= 0) {
        if (self->curItemId >= 0) {
            return 2;
        }
        if (itemId == 0x44 || itemId == 0x43) {
            int st = ((DriverStateView *)self->owner->ownerDriver)->state1f8;
            if (st == 0 || st == 1) {
                return 2;
            }
        }
        self->curItemId = itemId;
        ItemEffect_Projectile(self, idx, arg);
        return 0;
    }
    idx = ItemTable_FindEntryByIdStride24((ItemCatEntry24 *)(base + 0x1da4), 0xb, itemId);
    if (idx >= 0) {
        if (self->curItemId >= 0) {
            return 2;
        }
        self->curItemId = itemId;
        ItemEffect_Trap(self, idx, arg);
        return 0;
    }
    idx = ItemTable_FindEntryByIdStride12_v2((ItemCatEntry12 *)(base + 0x1eac), 0x9, itemId);
    if (idx >= 0) {
        if (self->curItemId >= 0) {
            return 2;
        }
        self->curItemId = itemId;
        ItemEffect_Explosion(self, idx, arg);
        return 0;
    }
    idx = ItemTable_FindEntryByIdStride12_v1((ItemCatEntry12 *)(base + 0x1f18), 0x1, itemId);
    if (idx >= 0) {
        void *bb;

        if (self->curItemId >= 0) {
            return 2;
        }
        self->curItemId = itemId;
        ItemEffect_TornadoLift(self->guard, self->owner->movement->transform);
        if (self->owner->strPcbGate20 != 0) {
            StrPcb_SetTimer3034_38(StrPcb_GetInstance(), 0xc, 2, lbl_806D26E4);
        }
        {
            KartMovementSpeedView *m = self->owner->movement;
            m->velX = lbl_806D26EC;
            m->velY = lbl_806D26EC;
            m->velZ = lbl_806D26EC;
            m->impact194 = lbl_806D26EC;
            m->impact198 = lbl_806D26EC;
            m->impact19c = lbl_806D26EC;
            m->impact1ac = lbl_806D26EC;
            m->impact1b0 = lbl_806D26EC;
            m->impact1b4 = lbl_806D26EC;
        }
        bb = self->owner->billboard;
        ShadowBillboard_SetField0x6CAndComputeAxis(bb, 2);
        {
            KartMovementSpeedView *m2 = self->owner->movement;
            float fx, fy, fz;
            fz = m2->transform[14];
            fy = m2->transform[13];
            fx = m2->transform[12];
            vt.x = fx;
            vt.y = fy;
            vt.z = fz;
        }
        ShadowBillboard_SetVec3At0x70(bb, &vt);
        /* HARD-BLOCK: target = addi r0,r31,0x1f18; add r5,r0,(idx*0xc);
         * lwz 0x4/0x8(r5). No probed C form reproduces the grouping. */
        *(ItemActPair *)&self->activeId = *(const ItemActPair *)&((ItemCatEntry12 *)(base + 0x1f18))[idx].valA;
        return 0;
    }
    idx = ItemTable_FindEntryByIdStride16((ItemCatEntry16 *)(base + 0x1f24), 0x1, itemId);
    if (idx >= 0) {
        void *bb2;

        if (self->curItemId >= 0) {
            return 2;
        }
        self->curItemId = itemId;
        /* HARD-BLOCK: target keeps idx<<4 in r29 and remats addi
         * r0,r31,0x1f24 per use; CW saves the full pointer instead. */
        ItemEffect_BossGrab(self->guard, self->owner->movement->transform, arg, ((ItemCatEntry16 *)(base + 0x1f24))[idx].valA);
        bb2 = self->owner->billboard;
        ShadowBillboard_SetField0x6CAndComputeAxis(bb2, 4);
        {
            KartMovementSpeedView *m3 = self->owner->movement;
            float gx, gy, gz;
            gz = m3->transform[14];
            gy = m3->transform[13];
            gx = m3->transform[12];
            vg.x = gx;
            vg.y = gy;
            vg.z = gz;
        }
        ShadowBillboard_SetVec3At0x70(bb2, &vg);
        if (self->owner->strPcbGate20 != 0) {
            StrPcb_SetTimer3034_38(StrPcb_GetInstance(), 0xc, 2, lbl_806D26E4);
        }
        {
            KartMovementSpeedView *m4 = self->owner->movement;
            m4->velX = lbl_806D26EC;
            m4->velY = lbl_806D26EC;
            m4->velZ = lbl_806D26EC;
            m4->impact194 = lbl_806D26EC;
            m4->impact198 = lbl_806D26EC;
            m4->impact19c = lbl_806D26EC;
            m4->impact1ac = lbl_806D26EC;
            m4->impact1b0 = lbl_806D26EC;
            m4->impact1b4 = lbl_806D26EC;
        }
        *(ItemActPair *)&self->activeId = *(const ItemActPair *)&((ItemCatEntry16 *)(base + 0x1f24))[idx].valB;
        return 0;
    }
    return 1;
}
#pragma exceptions reset
