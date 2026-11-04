#include "game/mapobject/mapobject17b_debug_private.h"
#include "dolphin/dvd.h"
#include "libc/string.h"

extern "C" {
char *strstr(const char *, const char *);
extern const char lbl_806D917C[3], lbl_806D9180[5];
extern const char *lbl_804917E0[37];
extern void *lbl_806D165C;
extern int lbl_806CFB7C;
void *Archive_GetCurrent(void *);
const char *HSD_ArchiveGetPublicName(void *, int);
void HSD_JObjClearFlagsAll(HSD_JObj *, unsigned int);
void HSD_JObjSetFlagsAll(HSD_JObj *, unsigned int);
void *fn_80180670(const char *, int);
void *fn_801816AC(const char *);
void fn_801804CC(void *, const char *);
void fn_80180458(void *);
void fn_801805AC(void *, int (*)(int,int,unsigned int,int,unsigned int));
void fn_801814C8();
void fn_8017E824(const char *);
void fn_8017DF00();
void OverlayText(int,int,int,const char *,...);
void fn_8017FF10(int,int,const char *,...);
void TransparentDraw_SortAndDispatch();
void CObj_DebugVizPathFlush(MapDebugCamera *);
void clNormal3D_Exec(clNormal3D *);
void Object_RenderJObjTree(clNormal3D *,int);
void GXDrawDone();
void Object_DtorWithGXSync(clNormal3D *,int);
void TransparentDraw_RemoveByOwner(int);
void SceneDrawList_Reset();
void SetCourseScene3D(int);
void fn_80181998(Vec3f *,Vec3f *,Vec3f *,Vec3f *,int,int,int,int,int);
void fn_80181B7C(Vec3f *,Vec3f *,int,int,int,int,int);
void fn_80181D28(Vec3f *,int,int,int,int,int);
}

extern "C" int fn_8017D660(int,int,unsigned int,int,unsigned int);

static inline void MapDebugListFiles(const char *base) {
                void *menu = lbl_806D165C;
                if (menu == 0) {
                    menu = fn_801816AC(base + 0x7D0);
                    if (menu == 0) return;
                    fn_801805AC(menu, fn_8017D660);
                }
                fn_80180458(menu);
                DVDDir dir;
                DVDDirEntry entry;
                if (DVDOpenDir(lbl_806D917C, &dir) != 1) return;
                while (DVDReadDir(&dir, &entry)) {
                    if (entry.isDir == 0) {
                        int filter = lbl_806D1630;
            if (filter != 0) {
                if (filter <= 26) {
                    char upper = filter + 0x40;
                    char lower = filter + 0x60;
                    if (entry.name[0] != upper && entry.name[0] != lower) continue;
                } else if (filter <= 36) {
                    char digit = filter + 0x15;
                    if (entry.name[0] != digit) continue;
                }
            }
                        if (strstr(entry.name, lbl_806D9180)) fn_801804CC(menu, entry.name);
                    }
                }
                DVDCloseDir(&dir);
}

static inline unsigned char MapDebugFindFile(char *dst, unsigned int index) {
    DVDDir dir;
    DVDDirEntry entry;
    if (dst == 0) return 0;
    unsigned int count = 0;
    if (DVDOpenDir(lbl_806D917C, &dir) != 1) return 0;
    while (DVDReadDir(&dir, &entry)) {
        if (entry.isDir == 0) {
            int filter = lbl_806D1630;
            if (filter != 0) {
                if (filter <= 26) {
                    char upper = filter + 0x40;
                    char lower = filter + 0x60;
                    if (entry.name[0] != upper && entry.name[0] != lower) continue;
                } else if (filter <= 36) {
                    char digit = filter + 0x15;
                    if (entry.name[0] != digit) continue;
                }
            }
            if (strstr(entry.name, lbl_806D9180)) {
                if (count == index) {
                    strcpy(dst, entry.name);
                    DVDCloseDir(&dir);
                    return 1;
                }
                count++;
            }
        }
    }
    DVDCloseDir(&dir);
    return 0;
}

static inline void MapDebugDrawPath() {
                clPathNode *node = lbl_806D163C;
                while (node) {
                    if (node == lbl_806D1640) {
                        fn_80181998(&node->points[0],&node->points[1],&node->points[2],&node->points[3],255,255,255,63,1);
                        fn_80181B7C(&node->points[0],&node->points[1],255,255,255,127,1);
                        fn_80181B7C(&node->points[1],&node->points[2],255,255,255,127,1);
                        fn_80181B7C(&node->points[2],&node->points[3],255,255,255,127,1);
                        fn_80181B7C(&node->points[3],&node->points[0],255,255,255,127,1);
                        fn_80181D28(&node->points[node->index],255,0,0,255,1);
                    } else fn_80181998(&node->points[0],&node->points[1],&node->points[2],&node->points[3],255,255,255,63,1);
                    node = node->next;
                }
}

extern "C" int fn_8017D660(int event, int unused, unsigned int item, int unused2, unsigned int selection) {
    const char *base = lbl_80376220;
    switch (event) {
    case 0:
        switch (selection) {
        case 9:
            if (lbl_806CFB85) {
                char filename[0x100];
                if (MapDebugFindFile(filename, item)) fn_8017E824(filename);
            }
            break;
        case 11: fn_801814C8(); break;
        case 3:
            if (lbl_806D1620 && *(void **)((char *)lbl_806D1620 + 0x24)) {
                void *archive = Archive_GetCurrent(*(void **)((char *)lbl_806D1620 + 0x24));
                void *menu = fn_80180670(base + 0x798, 0);
                if (menu) {
                    lbl_806D162C = 1;
                    for (int i = 0; ; i++) {
                        if (i == 0) fn_801804CC(menu, base + 0x7A8);
                        else {
                            const char *name = HSD_ArchiveGetPublicName(archive, i - 1);
                            if (name == 0) break;
                            if (strcmp(name, base + 0x7B4) != 0) fn_801804CC(menu, name);
                        }
                    }
                }
            }
            break;
        case 4: {
            void *menu = fn_80180670(base + 0x7C0, 0);
            if (menu) {
                lbl_806D162C = 2;
                for (int i = 0; i < 37; i++) fn_801804CC(menu, lbl_804917E0[i]);
            }
            break;
        }
        }
        return 0;
    case 1:
        switch (lbl_806D162C) {
        case 1:
            if (lbl_806D1620 && *(void **)((char *)lbl_806D1620 + 0x24)) {
                void *archive = Archive_GetCurrent(*(void **)((char *)lbl_806D1620 + 0x24));
                if (selection == 0) {
                    for (int i = 1; ; i++) {
                        const char *name = HSD_ArchiveGetPublicName(archive, i - 1);
                        if (name == 0) break;
                        if (strcmp(name, base + 0x7B4) != 0)
                            HSD_JObjClearFlagsAll(ResolveJointByName(lbl_806D1620, name), 0x10);
                    }
                } else {
                    for (int i = 1; ; i++) {
                        const char *name = HSD_ArchiveGetPublicName(archive, i - 1);
                        if (name == 0) break;
                        if (strcmp(name, base + 0x7B4) != 0) {
                            if ((unsigned int)i == selection)
                                HSD_JObjClearFlagsAll(ResolveJointByName(lbl_806D1620, name), 0x10);
                            else HSD_JObjSetFlagsAll(ResolveJointByName(lbl_806D1620, name), 0x10);
                        }
                    }
                }
            }
            break;
        case 2:
            if (selection < 37) {
                lbl_806D1630 = selection;
                MapDebugListFiles(base);
            }
            break;
        }
        lbl_806D162C = 0;
        return 0;
    case 3: fn_8017DF00(); return 0;
    case 4:
        OverlayText(1,0,25,base + 0x7DC);
        switch (lbl_806D1628) {
        case 0:
            fn_8017FF10(0,26,base + 0x7F4);
            fn_8017FF10(0,27,base + 0x814);
            fn_8017FF10(0,28,base + 0x838);
            fn_8017FF10(0,29,base + 0x850);
            break;
        case 1:
            fn_8017FF10(0,0,base + 0x86C,lbl_80677D00.x,lbl_80677D00.z);
            fn_8017FF10(0,26,base + 0x87C);
            fn_8017FF10(0,27,base + 0x8A0);
            fn_8017FF10(0,28,base + 0x8B0);
            break;
        case 2:
            fn_8017FF10(0,0,base + 0x86C,lbl_80677D00.x,lbl_80677D00.z);
            break;
        }
        if (lbl_806D1618 && lbl_806D1620 && lbl_806D1618->Begin() == 1) {
            TransparentDraw_SortAndDispatch();
            CObj_DebugVizPathFlush(lbl_806D1618);
            if (lbl_806CFB84) clNormal3D_Exec(lbl_806D1620);
            Object_RenderJObjTree(lbl_806D1620, 7);
            if (lbl_806D1628 == 2) {
                MapDebugDrawPath();
            }
            lbl_806D1618->End();
        }
        return 0;
    case 2:
        GXDrawDone();
        while (lbl_806D1640) MapDebugRemoveNode(lbl_806D1640);
        if (lbl_806D1620) {
            Object_DtorWithGXSync(lbl_806D1620,1);
            lbl_806D1620 = 0;
        }
        if (lbl_806CFB7C >= 0) {
            TransparentDraw_RemoveByOwner(lbl_806CFB7C);
            lbl_806CFB7C = -1;
        }
        SceneDrawList_Reset();
        if (lbl_806D1618) {
            delete lbl_806D1618;
            lbl_806D1618 = 0;
        }
        SetCourseScene3D(0);
        if (lbl_806CFB85 == 0) {
            if (lbl_806CFBA1 != 1) lbl_806CFBA1 = 1;
            lbl_806CFB85 = 1;
        }
        return 0;
    }
    return 0;
}
