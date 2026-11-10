# c24_scene_fn_801502AC_partial

Source: Codex worker c24_a21_20261109 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

Best natural C++ partial: 97.068184%, 880 B. Reuses the existing matched SceneCache classes. Residual is the first info/id pointer (target lwzu and r29, source lwz +4 and r28), cascading self/name/index slot registers, and model slot CSE. Separate helper stages worsened saved-register pressure; integer-id view + helper returned identical score. No pragma/permuter probes. Patch below is against the untouched assignment source; keep as WIP only.

```diff
--- a/src/game/Scene_8014E0C4.cpp
+++ b/src/game/Scene_8014E0C4.cpp
@@ -500,7 +500,7 @@
 extern unsigned int lbl_806D8108;
 void HSD_CObjAnim(void *cobj);
 void HSD_CObjReqAnim(void *cobj, float frame);
-extern void JObj_Hide();
+void JObj_Hide(void *root, void *jobj, int flags);
 extern void Scene3D_Init();
 extern void SceneModel_Init();
 void clNormal3D_Exec(void *o);
@@ -1086,7 +1086,7 @@
 void fn_8014FEFC(TextPanelB *self);
 void fn_80150004(TextPanel *self);
 asm void fn_801500F4(void);
-asm void fn_801502AC(void);
+void fn_801502AC(RaceScene *self, int part);
 unsigned char fn_80150924(unsigned char *o);
 RaceScene *fn_8015092C(RaceScene *self, short flag);
 void fn_80150BE4(VObj *p);
@@ -1165,7 +1165,6 @@
 
 
 __declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; void *f13; unsigned int f14; unsigned int f15; void *f16; unsigned int f17; void *f18; unsigned int f19; unsigned int f20; void *f21; } extab_fn_801500F4 = { 0x300A0000, 0x00000060, 0x00050038, 0x00000094, 0x00000030, 0x000000D4, 0x00000038, 0x000000DC, 0x00090044, 0x00000120, 0x000C0038, 0x00000000, 0x0A80001A, (void *)&MemoryManager_TimedFree, 0x8680001D, 0x00000000, (void *)&dtor_801577D4, 0x0A80001C, (void *)&MemoryManager_Free, 0x8680001D, 0x00000000, (void *)&dtor_801577D4 };
-__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; void *f9; unsigned int f10; void *f11; unsigned int f12; void *f13; } extab_fn_801502AC = { 0x380A0000, 0x0000006C, 0x00000020, 0x00000198, 0x00000028, 0x000001C8, 0x00000030, 0x00000000, 0x8A800019, (void *)&MemoryManager_TimedFree, 0x8A80001A, (void *)&MemoryManager_TimedFree, 0x8A800019, (void *)&MemoryManager_TimedFree };
 
 
 
@@ -1211,6 +1210,32 @@
 
 
 #pragma section R ".extabindex_user"
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
+
 
 
 
@@ -1236,9 +1261,6 @@
 
 __declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_801500F4 = {
     (void *)&fn_801500F4, 0x000001B8, (void *)&extab_fn_801500F4
-};
-__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_801502AC = {
-    (void *)&fn_801502AC, 0x00000370, (void *)&extab_fn_801502AC
 };
 
 
@@ -3709,244 +3731,50 @@
     blr
 }
 
-extern "C" asm void fn_801502AC(void) { /* 0x801502AC size:0x370 */
-    nofralloc
-    stwu r1, -0x30(r1)
-    mflr r0
-    lis r5, Scene_8014E0C4_rodata_80363D30@ha
-    stw r0, 0x34(r1)
-    mulli r0, r4, 0x18
-    stmw r25, 0x14(r1)
-    addi r31, r5, Scene_8014E0C4_rodata_80363D30@l
-    mr r27, r3
-    addi r3, r31, 0x31c0
-    add r29, r3, r0
-    lwzu r0, 0x4(r29)
-    cmpwi r0, -0x1
-    beq fn_801502AC_L_80150608
-    slwi r30, r4, 2
-    slwi r4, r0, 2
-    add r26, r27, r30
-    addi r3, r31, 0x638
-    lwz r0, 0x28(r26)
-    lwzx r28, r3, r4
-    cmplwi r0, 0x0
-    bne fn_801502AC_L_80150418
-    li r3, 0x3090
-    bl Alloc
-    mr. r25, r3
-    beq fn_801502AC_L_80150334
-    mr r4, r28
-    bl Scene3D_Init
-    lis r3, lbl_80419EF8@ha
-    lfs f1, lbl_806D806C(r2)
-    addi r0, r3, lbl_80419EF8@l
-    lfs f0, lbl_806D8064(r2)
-    stw r0, 0x0(r25)
-    stfs f1, 0x3088(r25)
-    stfs f0, 0x308c(r25)
-    fn_801502AC_L_80150334:
-    stw r25, 0x28(r26)
-    lwz r25, 0x28(r26)
-    cmplwi r25, 0x0
-    beq fn_801502AC_L_801503C4
-    lwz r0, 0x4(r25)
-    cmplwi r0, 0x0
-    beq fn_801502AC_L_801503C4
-    li r0, 0x1
-    lfs f1, lbl_806D8064(r2)
-    stb r0, 0x3084(r25)
-    lfs f0, lbl_806D8068(r2)
-    stfs f1, 0x308c(r25)
-    stfs f0, 0x3088(r25)
-    lwz r3, 0x2c(r25)
-    cmplwi r3, 0x0
-    bne fn_801502AC_L_8015037C
-    li r4, 0x0
-    b fn_801502AC_L_801503A8
-    fn_801502AC_L_8015037C:
-    lwz r3, 0x4(r3)
-    cmplwi r3, 0x0
-    bne fn_801502AC_L_80150390
-    li r4, 0x0
-    b fn_801502AC_L_801503A8
-    fn_801502AC_L_80150390:
-    lwz r3, 0x4(r3)
-    cmplwi r3, 0x0
-    bne fn_801502AC_L_801503A4
-    li r4, 0x0
-    b fn_801502AC_L_801503A8
-    fn_801502AC_L_801503A4:
-    lwz r4, 0x0(r3)
-    fn_801502AC_L_801503A8:
-    lwz r3, 0x4(r25)
-    bl HSD_CObjAddAnim
-    lwz r3, 0x4(r25)
-    lfs f1, 0x308c(r25)
-    bl HSD_CObjReqAnim
-    lwz r3, 0x4(r25)
-    bl HSD_CObjAnim
-    fn_801502AC_L_801503C4:
-    lwz r25, 0x28(r26)
-    cmplwi r25, 0x0
-    beq fn_801502AC_L_80150418
-    lfs f0, lbl_806D806C(r2)
-    lfs f1, 0x3088(r25)
-    fcmpu cr0, f0, f1
-    beq fn_801502AC_L_80150418
-    lbz r0, 0x3084(r25)
-    cmplwi r0, 0x0
-    beq fn_801502AC_L_801503F8
-    li r0, 0x0
-    stb r0, 0x3084(r25)
-    b fn_801502AC_L_80150404
-    fn_801502AC_L_801503F8:
-    lfs f0, 0x308c(r25)
-    fadds f0, f0, f1
-    stfs f0, 0x308c(r25)
-    fn_801502AC_L_80150404:
-    lwz r3, 0x4(r25)
-    lfs f1, 0x308c(r25)
-    bl HSD_CObjReqAnim
-    lwz r3, 0x4(r25)
-    bl HSD_CObjAnim
-    fn_801502AC_L_80150418:
-    add r25, r27, r30
-    lwz r0, 0x7c(r25)
-    cmplwi r0, 0x0
-    bne fn_801502AC_L_80150448
-    li r3, 0x28
-    bl Alloc
-    mr. r26, r3
-    beq fn_801502AC_L_80150444
-    mr r4, r28
-    li r5, 0x1
-    bl SceneModel_Init
-    fn_801502AC_L_80150444:
-    stw r26, 0x7c(r25)
-    fn_801502AC_L_80150448:
-    add r30, r27, r30
-    lwz r0, 0xd0(r30)
-    cmplwi r0, 0x0
-    bne fn_801502AC_L_80150608
-    li r3, 0x5c
-    bl Alloc
-    mr. r25, r3
-    beq fn_801502AC_L_80150474
-    mr r4, r28
-    li r5, 0x0
-    bl clNormal3D_Construct
-    fn_801502AC_L_80150474:
-    stw r25, 0xd0(r30)
-    lwz r3, 0xd0(r30)
-    cmplwi r3, 0x0
-    beq fn_801502AC_L_8015049C
-    lfs f1, lbl_806D8064(r2)
-    li r4, 0x0
-    lfs f2, lbl_806D8068(r2)
-    fmr f3, f1
-    fmr f4, f1
-    bl clNormal3D_SetScale
-    fn_801502AC_L_8015049C:
-    lwz r3, 0xd0(r30)
-    cmplwi r3, 0x0
-    beq fn_801502AC_L_801504AC
-    bl clNormal3D_Exec
-    fn_801502AC_L_801504AC:
-    lwz r0, 0x0(r29)
-    cmpwi r0, 0x15
-    bne fn_801502AC_L_80150608
-    lwz r3, 0xd0(r30)
-    addi r4, r31, 0x3938
-    bl ResolveJointByName
-    mr r4, r3
-    lwz r3, 0xd0(r30)
-    li r5, 0x10
-    bl JObj_Hide
-    lwz r3, 0xd0(r30)
-    addi r4, r31, 0x394c
-    bl ResolveJointByName
-    mr r4, r3
-    lwz r3, 0xd0(r30)
-    li r5, 0x10
-    bl JObj_Hide
-    lwz r3, 0xd0(r30)
-    addi r4, r31, 0x3960
-    bl ResolveJointByName
-    mr r4, r3
-    lwz r3, 0xd0(r30)
-    li r5, 0x10
-    bl JObj_Hide
-    lwz r3, 0xd0(r30)
-    addi r4, r31, 0x3974
-    bl ResolveJointByName
-    mr r4, r3
-    lwz r3, 0xd0(r30)
-    li r5, 0x10
-    bl JObj_Hide
-    lwz r3, 0xd0(r30)
-    addi r4, r31, 0x3988
-    bl ResolveJointByName
-    mr r4, r3
-    lwz r3, 0xd0(r30)
-    li r5, 0x10
-    bl JObj_Hide
-    lwz r3, 0xd0(r30)
-    addi r4, r31, 0x399c
-    bl ResolveJointByName
-    mr r4, r3
-    lwz r3, 0xd0(r30)
-    li r5, 0x10
-    bl JObj_Hide
-    lwz r3, 0xd0(r30)
-    addi r4, r31, 0x39b0
-    bl ResolveJointByName
-    mr r4, r3
-    lwz r3, 0xd0(r30)
-    li r5, 0x10
-    bl JObj_Hide
-    lwz r3, 0xd0(r30)
-    addi r4, r31, 0x39c4
-    bl ResolveJointByName
-    mr r4, r3
-    lwz r3, 0xd0(r30)
-    li r5, 0x10
-    bl JObj_Hide
-    lwz r3, 0xd0(r30)
-    addi r4, r31, 0x39d8
-    bl ResolveJointByName
-    mr r4, r3
-    lwz r3, 0xd0(r30)
-    li r5, 0x10
-    bl JObj_Hide
-    lwz r3, 0xd0(r30)
-    addi r4, r31, 0x39ec
-    bl ResolveJointByName
-    mr r4, r3
-    lwz r3, 0xd0(r30)
-    li r5, 0x10
-    bl JObj_Hide
-    lwz r3, 0xd0(r30)
-    addi r4, r31, 0x3a00
-    bl ResolveJointByName
-    mr r4, r3
-    lwz r3, 0xd0(r30)
-    li r5, 0x10
-    bl JObj_Hide
-    lwz r3, 0xd0(r30)
-    addi r4, r31, 0x3a14
-    bl ResolveJointByName
-    mr r4, r3
-    lwz r3, 0xd0(r30)
-    li r5, 0x10
-    bl JObj_Hide
-    fn_801502AC_L_80150608:
-    lmw r25, 0x14(r1)
-    lwz r0, 0x34(r1)
-    mtlr r0
-    addi r1, r1, 0x30
-    blr
-}
+#pragma use_lmw_stmw on
+extern "C" void fn_801502AC(RaceScene *self, int part) {
+    const CourseModeInfo *info = &Scene_8014E0C4_rodata_80366EF0[part];
+    const char *name;
+    SceneCacheAnimScene *cam;
+    if (info->id == -1) return;
+    name = ((const char *const *)&Scene_8014E0C4_rodata_80364368)[info->id];
+    if (self->objs[part] == 0) {
+        self->objs[part] = (RaceCam *)new SceneCacheAnimScene(name);
+        cam = (SceneCacheAnimScene *)self->objs[part];
+        if (cam != 0) cam->start();
+        SceneCacheAnimScene *c = (SceneCacheAnimScene *)self->objs[part];
+        if (c != 0) {
+            if (-1.0f != c->speed) {
+                if (c->active) c->active = 0;
+                else c->frame += c->speed;
+                HSD_CObjReqAnim(c->camera, c->frame);
+                HSD_CObjAnim(c->camera);
+            }
+        }
+    }
+    if (self->lists[part] == 0) self->lists[part] = new SceneCacheModel(name, 1);
+    if (self->models[part] == 0) {
+        self->models[part] = new SceneCacheNormal(name, 0);
+        if (self->models[part] != 0)
+            clNormal3D_SetScale(self->models[part], 0, 0.0f, 1.0f, 0.0f, 0.0f);
+        if (self->models[part] != 0) clNormal3D_Exec(self->models[part]);
+        if (info->id == 0x15) {
+            JObj_Hide(self->models[part], ResolveJointByName(self->models[part], (char *)lbl_80367668), 0x10);
+            JObj_Hide(self->models[part], ResolveJointByName(self->models[part], (char *)lbl_8036767C), 0x10);
+            JObj_Hide(self->models[part], ResolveJointByName(self->models[part], (char *)lbl_80367690), 0x10);
+            JObj_Hide(self->models[part], ResolveJointByName(self->models[part], (char *)lbl_803676A4), 0x10);
+            JObj_Hide(self->models[part], ResolveJointByName(self->models[part], (char *)lbl_803676B8), 0x10);
+            JObj_Hide(self->models[part], ResolveJointByName(self->models[part], (char *)lbl_803676CC), 0x10);
+            JObj_Hide(self->models[part], ResolveJointByName(self->models[part], (char *)lbl_803676E0), 0x10);
+            JObj_Hide(self->models[part], ResolveJointByName(self->models[part], (char *)lbl_803676F4), 0x10);
+            JObj_Hide(self->models[part], ResolveJointByName(self->models[part], (char *)lbl_80367708), 0x10);
+            JObj_Hide(self->models[part], ResolveJointByName(self->models[part], (char *)lbl_8036771C), 0x10);
+            JObj_Hide(self->models[part], ResolveJointByName(self->models[part], (char *)lbl_80367730), 0x10);
+            JObj_Hide(self->models[part], ResolveJointByName(self->models[part], (char *)lbl_80367744), 0x10);
+        }
+    }
+}
+#pragma use_lmw_stmw reset
 
 
 class VObjModel : public VObj {
```
