/* Game setting test-menu pages: entry, input and drawing phases. */
#pragma cplusplus on
#include "game/TestMenuPage.h"

#include "game/GameSetting_private.h"

extern "C" {
    extern MenuItem lbl_803FC444[], lbl_803FC2D0[], lbl_803FC174[];
    extern const char lbl_806D2D94[4], lbl_806D2DA4[6], lbl_806D2DAC[3];
    extern const char lbl_806D2DCC[3], lbl_806D2E50[4], lbl_806D2E70[6];
    extern const char lbl_806D2E78[5], lbl_806D2E80[4], lbl_806D2E84[5];
    extern const char lbl_806D2E8C[8], lbl_806D2E94[7];
    void Backup_PublishShadowCopy_Inline(void);
    void PcbIdToIpAndModify(int);
    GamePcbSlot *PcbSlot_GetByIndex(int);
    unsigned char PcbSlot_IsReadyByIndex(int);
    int PcbSync_CountJoinedPcbs(void);
    void VBlankValue_Set(int);
    void ServiceEnable_Set(int);
    void ServiceValue_Set(int);
}

/* Keep virtual input dispatch in the shared test-menu C++ interface. */
static inline unsigned char GameSetting_Pressed(InputPlayer *pl, int mask)
{
    return pl->Pressed(mask);
}
typedef struct InputPlayer InputPlayer;
typedef struct TestPage TestPage;
typedef struct GameSettings GameSettings;
#pragma cplusplus off
/* Branchless nonzero normalization, also used by CardSlotFlag.cpp. */
static inline unsigned int GameSetting_Flag(unsigned int value)
{
    return ((0U - value) | value) >> 31;
}

#pragma exceptions on
#pragma use_lmw_stmw on
int GameSetting_Page_VariantA(TestPage *self, int phase)
{
    InputPlayer *pl;
    GameSettings *cs;
    int joined;
    const char *strings = lbl_8030E598;
    if (phase == 0) self->cursor = 6;
    if (phase == 1) {
        pl = InputMgr_GetPlayer(GetInputManager(), 0);
        if (GameSetting_Pressed(pl, 0x800)) {
            self->blink = 0x1F;
            if (++self->cursor > 6) self->cursor = 0;
            if (((GameSettings *)self->data)->cabinet != 1 && self->cursor == 4) ++self->cursor;
        }
        if (((GameSettings *)self->data)->cabinet != 1 && PcbSlot_IsReadyByIndex(0)) {
            ((GameSettings *)self->data)->linkOption = GameSetting_Flag(PcbSlot_GetByIndex(0)->flags & 1);
        }
        if (GameSetting_Pressed(pl, 0x1000)) {
            if (self->cursor == 0) {
                cs = (GameSettings *)self->data;
                if (++cs->cabinet > 4) ((GameSettings *)self->data)->cabinet = 1;
            }
            if (self->cursor == 1) {
                cs = (GameSettings *)self->data;
                cs->mode = (cs->mode + 1) % 3;
            }
            if (self->cursor == 2) {
                cs = (GameSettings *)self->data;
                if (cs->vblank != 0) cs->vblank = 0;
                else cs->vblank = 1;
            }
            if (self->cursor == 3) {
                cs = (GameSettings *)self->data;
                if (cs->option26 != 0) cs->option26 = 0;
                else cs->option26 = 1;
            }
            if (self->cursor == 4) {
                cs = (GameSettings *)self->data;
                if (cs->linkOption != 0) cs->linkOption = 0;
                else cs->linkOption = 1;
            }
            if (self->cursor == 5) {
                cs = (GameSettings *)self->data;
                if (cs->flag44 != 0) {
                    if (cs->flag45 != 0) cs->flag45 = 0;
                    else {
                        cs->flag44 = 0;
                        ((GameSettings *)self->data)->flag45 = 1;
                    }
                } else cs->flag44 = 1;
            }
            if (self->cursor == 6) {
                VBlankValue_Set(((GameSettings *)self->data)->vblank == 0);
                Backup_PublishShadowCopy_Inline();
                PcbIdToIpAndModify(0);
                self->next = 0;
            }
        }
    }
    if (phase == 2) {
        joined = PcbSync_CountJoinedPcbs();
        TestPage_DrawItems(self, lbl_803FC444, self->cursor + 3);
        if (self->text != 0) {
            DrawText(self->text, 0x16c, 0x30, 2, 1.0f, lbl_806D2DA4);
            if (joined <= 1) {
                DrawText(self->text, 0x150, 0x60, 7, 1.0f, lbl_806D2D94);
            } else {
                DrawText(self->text, 0x150, 0x60, 7, 1.0f, lbl_806D2E70, joined);
            }
            if (((GameSettings *)self->data)->cabinet == 1) {
                DrawText(self->text, 0x15e, 0x90, 2, 1.0f, lbl_806D2DCC, ((GameSettings *)self->data)->cabinet);
            } else {
                DrawText(self->text, 0x15e, 0x90, 4, 1.0f, lbl_806D2DCC, ((GameSettings *)self->data)->cabinet);
            }
            if (((GameSettings *)self->data)->mode == 0) {
                DrawText(self->text, 0x15e, 0xc0, 4, 1.0f, lbl_806D2D94);
            } else if (((GameSettings *)self->data)->mode == 1) {
                DrawText(self->text, 0x15e, 0xc0, 4, 1.0f, strings + 0x2708);
            } else {
                DrawText(self->text, 0x15e, 0xc0, 2, 1.0f, strings + 0x2714);
            }
            if (((GameSettings *)self->data)->vblank != 0) {
                DrawText(self->text, 0x15e, 0xd8, 2, 1.0f, lbl_806D2DAC);
            } else {
                DrawText(self->text, 0x15e, 0xd8, 4, 1.0f, lbl_806D2D94);
            }
            if (((GameSettings *)self->data)->option26 != 0) {
                DrawText(self->text, 0x15e, 0xf0, 4, 1.0f, lbl_806D2E78);
            } else {
                DrawText(self->text, 0x15e, 0xf0, 2, 1.0f, lbl_806D2E80);
            }
            if (((GameSettings *)self->data)->cabinet == 1) {
                if (self->cursor != 4 || self->blink <= 0x1E) {
                    DrawText(self->text, 0x2a, 0x108, 7, 1.0f, strings + 0x2720);
                }
                if (((GameSettings *)self->data)->linkOption != 0) {
                    DrawText(self->text, 0x15e, 0x108, 4, 1.0f, lbl_806D2DAC);
                } else {
                    DrawText(self->text, 0x15e, 0x108, 2, 1.0f, lbl_806D2D94);
                }
            } else {
                if (((GameSettings *)self->data)->linkOption != 0) {
                    DrawText(self->text, 0x2a, 0x108, 3, 1.0f, strings + 0x272c);
                } else {
                    DrawText(self->text, 0x2a, 0x108, 3, 1.0f, strings + 0x2748);
                }
            }
            if (((GameSettings *)self->data)->flag44 != 0) {
                if (((GameSettings *)self->data)->flag45 != 0) {
                    DrawText(self->text, 0x15e, 0x120, 2, 1.0f, strings + 0x2764);
                } else {
                    DrawText(self->text, 0x15e, 0x120, 4, 1.0f, lbl_806D2E84);
                }
            } else {
                DrawText(self->text, 0x15e, 0x120, 4, 1.0f, lbl_806D2E50);
            }
        }
    }
    return 1;
}
#pragma use_lmw_stmw reset
#pragma exceptions reset
#pragma exceptions on
#pragma use_lmw_stmw on
int GameSetting_Page_VariantB(TestPage *self, int phase)
{
    InputPlayer *pl;
    GameSettings *cs;
    int joined;
    const char *strings = lbl_8030E598;
    if (phase == 0) self->cursor = 8;
    if (phase == 1) {
        pl = InputMgr_GetPlayer(GetInputManager(), 0);
        if (GameSetting_Pressed(pl, 0x800)) {
            self->blink = 0x1F;
            if (++self->cursor > 8) self->cursor = 0;
            if (((GameSettings *)self->data)->cabinet != 1 && self->cursor == 1) ++self->cursor;
            if (((GameSettings *)self->data)->serviceEnabled == 0 && self->cursor == 2) ++self->cursor;
            if (((GameSettings *)self->data)->cabinet != 1 && self->cursor == 6) ++self->cursor;
        }
        if (((GameSettings *)self->data)->cabinet != 1 && PcbSlot_IsReadyByIndex(0)) {
            ((GameSettings *)self->data)->serviceEnabled = GameSetting_Flag((PcbSlot_GetByIndex(0)->flags >> 4) & 1);
            ((GameSettings *)self->data)->linkOption = GameSetting_Flag(PcbSlot_GetByIndex(0)->flags & 1);
        }
        if (GameSetting_Pressed(pl, 0x1000)) {
            if (self->cursor == 0) {
                cs = (GameSettings *)self->data;
                if (++cs->cabinet > 4) ((GameSettings *)self->data)->cabinet = 1;
            }
            if (self->cursor == 1 && ((GameSettings *)self->data)->cabinet == 1) {
                cs = (GameSettings *)self->data;
                if (cs->serviceEnabled != 0) cs->serviceEnabled = 0;
                else cs->serviceEnabled = 1;
            }
            if (self->cursor == 2) {
                cs = (GameSettings *)self->data;
                if (cs->serviceValue != 0) cs->serviceValue = 0;
                else cs->serviceValue = 1;
            }
            if (self->cursor == 3) {
                cs = (GameSettings *)self->data;
                cs->mode = (cs->mode + 1) % 3;
            }
            if (self->cursor == 4) {
                cs = (GameSettings *)self->data;
                if (cs->vblank != 0) cs->vblank = 0;
                else cs->vblank = 1;
            }
            if (self->cursor == 5) {
                cs = (GameSettings *)self->data;
                if (cs->option26 != 0) cs->option26 = 0;
                else cs->option26 = 1;
            }
            if (self->cursor == 6) {
                cs = (GameSettings *)self->data;
                if (cs->linkOption != 0) cs->linkOption = 0;
                else cs->linkOption = 1;
            }
            if (self->cursor == 7) {
                cs = (GameSettings *)self->data;
                if (cs->flag44 != 0) {
                    if (cs->flag45 != 0) cs->flag45 = 0;
                    else {
                        cs->flag44 = 0;
                        ((GameSettings *)self->data)->flag45 = 1;
                    }
                } else cs->flag44 = 1;
            }
            if (self->cursor == 8) {
                ServiceEnable_Set(((GameSettings *)self->data)->serviceEnabled);
                ServiceValue_Set(((GameSettings *)self->data)->serviceValue == 0);
                VBlankValue_Set(((GameSettings *)self->data)->vblank == 0);
                Backup_PublishShadowCopy_Inline();
                PcbIdToIpAndModify(0);
                self->next = 0;
            }
        }
    }
    if (phase == 2) {
        joined = PcbSync_CountJoinedPcbs();
        TestPage_DrawItems(self, lbl_803FC2D0, self->cursor + 3);
        if (self->text != 0) {
            DrawText(self->text, 0x16c, 0x30, 2, 1.0f, lbl_806D2DA4);
            if (joined <= 1) {
                DrawText(self->text, 0x150, 0x60, 7, 1.0f, lbl_806D2D94);
            } else {
                DrawText(self->text, 0x150, 0x60, 7, 1.0f, lbl_806D2E70, joined);
            }
            if (((GameSettings *)self->data)->cabinet == 1) {
                DrawText(self->text, 0x15e, 0x90, 2, 1.0f, lbl_806D2DCC, ((GameSettings *)self->data)->cabinet);
            } else {
                DrawText(self->text, 0x15e, 0x90, 4, 1.0f, lbl_806D2DCC, ((GameSettings *)self->data)->cabinet);
            }
            if (((GameSettings *)self->data)->cabinet == 1) {
                if (self->cursor != 1 || self->blink <= 0x1E) {
                    DrawText(self->text, 0x2a, 0xc0, 7, 1.0f, strings + 0x2770);
                }
                if (((GameSettings *)self->data)->serviceEnabled != 0) {
                    DrawText(self->text, 0x15e, 0xc0, 2, 1.0f, strings + 0x277c);
                } else {
                    DrawText(self->text, 0x15e, 0xc0, 4, 1.0f, strings + 0x2788);
                }
            } else {
                if (((GameSettings *)self->data)->serviceEnabled != 0) {
                    DrawText(self->text, 0x2a, 0xc0, 3, 1.0f, strings + 0x2798);
                } else {
                    DrawText(self->text, 0x2a, 0xc0, 3, 1.0f, strings + 0x27b8);
                }
            }
            if (((GameSettings *)self->data)->serviceEnabled == 1) {
                if (self->cursor != 2 || self->blink <= 0x1E) {
                    DrawText(self->text, 0x2a, 0xd8, 7, 1.0f, strings + 0x27dc);
                }
                if (((GameSettings *)self->data)->serviceValue != 0) {
                    DrawText(self->text, 0x15e, 0xd8, 2, 1.0f, lbl_806D2DAC);
                } else {
                    DrawText(self->text, 0x15e, 0xd8, 4, 1.0f, lbl_806D2D94);
                }
            } else {
                if (((GameSettings *)self->data)->serviceValue != 0) {
                    DrawText(self->text, 0x2a, 0xd8, 3, 1.0f, strings + 0x27e8);
                } else {
                    DrawText(self->text, 0x2a, 0xd8, 3, 1.0f, strings + 0x2804);
                }
            }
            if (((GameSettings *)self->data)->mode == 0) {
                DrawText(self->text, 0x15e, 0xf0, 4, 1.0f, lbl_806D2D94);
            } else if (((GameSettings *)self->data)->mode == 1) {
                DrawText(self->text, 0x15e, 0xf0, 4, 1.0f, strings + 0x2708);
            } else {
                DrawText(self->text, 0x15e, 0xf0, 2, 1.0f, strings + 0x2714);
            }
            if (((GameSettings *)self->data)->vblank != 0) {
                DrawText(self->text, 0x15e, 0x108, 2, 1.0f, lbl_806D2DAC);
            } else {
                DrawText(self->text, 0x15e, 0x108, 4, 1.0f, lbl_806D2D94);
            }
            if (((GameSettings *)self->data)->option26 != 0) {
                DrawText(self->text, 0x15e, 0x120, 2, 1.0f, lbl_806D2E78);
            } else {
                DrawText(self->text, 0x15e, 0x120, 4, 1.0f, lbl_806D2E80);
            }
            if (((GameSettings *)self->data)->cabinet == 1) {
                if (self->cursor != 6 || self->blink <= 0x1E) {
                    DrawText(self->text, 0x2a, 0x138, 7, 1.0f, strings + 0x2720);
                }
                if (((GameSettings *)self->data)->linkOption != 0) {
                    DrawText(self->text, 0x15e, 0x138, 4, 1.0f, lbl_806D2DAC);
                } else {
                    DrawText(self->text, 0x15e, 0x138, 2, 1.0f, lbl_806D2D94);
                }
            } else {
                if (((GameSettings *)self->data)->linkOption != 0) {
                    DrawText(self->text, 0x2a, 0x138, 3, 1.0f, strings + 0x272c);
                } else {
                    DrawText(self->text, 0x2a, 0x138, 3, 1.0f, strings + 0x2748);
                }
            }
            if (((GameSettings *)self->data)->flag44 != 0) {
                if (((GameSettings *)self->data)->flag45 != 0) {
                    DrawText(self->text, 0x15e, 0x150, 2, 1.0f, strings + 0x2764);
                } else {
                    DrawText(self->text, 0x15e, 0x150, 4, 1.0f, lbl_806D2E84);
                }
            } else {
                DrawText(self->text, 0x15e, 0x150, 4, 1.0f, lbl_806D2E50);
            }
        }
    }
    return 1;
}
#pragma use_lmw_stmw reset
#pragma exceptions reset
#pragma exceptions on
#pragma use_lmw_stmw on
int GameSetting_Page(TestPage *self, int phase)
{
    InputPlayer *pl;
    GameSettings *cs;
    int joined;
    const char *strings = lbl_8030E598;
    if (phase == 0) self->cursor = 7;
    if (phase == 1) {
        pl = InputMgr_GetPlayer(GetInputManager(), 0);
        if (GameSetting_Pressed(pl, 0x800)) {
            self->blink = 0x1F;
            if (++self->cursor > 7) self->cursor = 0;
            if (((GameSettings *)self->data)->cabinet != 1 && self->cursor == 5) ++self->cursor;
        }
        if (((GameSettings *)self->data)->cabinet != 1 && PcbSlot_IsReadyByIndex(0)) {
            ((GameSettings *)self->data)->serviceEnabled = GameSetting_Flag((PcbSlot_GetByIndex(0)->flags >> 4) & 1);
            ((GameSettings *)self->data)->linkOption = GameSetting_Flag(PcbSlot_GetByIndex(0)->flags & 1);
        }
        if (GameSetting_Pressed(pl, 0x1000)) {
            if (self->cursor == 0) {
                cs = (GameSettings *)self->data;
                if (++cs->cabinet > 4) ((GameSettings *)self->data)->cabinet = 1;
            }
            if (self->cursor == 1) {
                cs = (GameSettings *)self->data;
                if (cs->serviceValue != 0) cs->serviceValue = 0;
                else cs->serviceValue = 1;
            }
            if (self->cursor == 2) {
                cs = (GameSettings *)self->data;
                cs->mode = (cs->mode + 1) % 3;
            }
            if (self->cursor == 3) {
                cs = (GameSettings *)self->data;
                if (cs->vblank != 0) cs->vblank = 0;
                else cs->vblank = 1;
            }
            if (self->cursor == 4) {
                cs = (GameSettings *)self->data;
                if (cs->option27 != 0) cs->option27 = 0;
                else cs->option27 = 1;
            }
            if (self->cursor == 5) {
                cs = (GameSettings *)self->data;
                if (cs->linkOption != 0) cs->linkOption = 0;
                else cs->linkOption = 1;
            }
            if (self->cursor == 6) {
                cs = (GameSettings *)self->data;
                if (cs->flag44 != 0) {
                    if (cs->flag45 != 0) cs->flag45 = 0;
                    else {
                        cs->flag44 = 0;
                        ((GameSettings *)self->data)->flag45 = 1;
                    }
                } else cs->flag44 = 1;
            }
            if (self->cursor == 7) {
                ServiceEnable_Set(((GameSettings *)self->data)->serviceEnabled);
                ServiceValue_Set(((GameSettings *)self->data)->serviceValue == 0);
                VBlankValue_Set(((GameSettings *)self->data)->vblank == 0);
                Backup_PublishShadowCopy_Inline();
                PcbIdToIpAndModify(0);
                self->next = 0;
            }
        }
    }
    if (phase == 2) {
        joined = PcbSync_CountJoinedPcbs();
        TestPage_DrawItems(self, lbl_803FC174, self->cursor + 3);
        if (self->text != 0) {
            DrawText(self->text, 0x16c, 0x30, 2, 1.0f, lbl_806D2DA4);
            if (joined <= 1) {
                DrawText(self->text, 0x150, 0x60, 7, 1.0f, lbl_806D2D94);
            } else {
                DrawText(self->text, 0x150, 0x60, 7, 1.0f, lbl_806D2E70, joined);
            }
            if (((GameSettings *)self->data)->cabinet == 1) {
                DrawText(self->text, 0x15e, 0x90, 2, 1.0f, lbl_806D2DCC, ((GameSettings *)self->data)->cabinet);
            } else {
                DrawText(self->text, 0x15e, 0x90, 4, 1.0f, lbl_806D2DCC, ((GameSettings *)self->data)->cabinet);
            }
            if (((GameSettings *)self->data)->serviceEnabled == 1) {
                if (self->cursor != 1 || self->blink <= 0x1E) {
                    DrawText(self->text, 0x2a, 0xc0, 7, 1.0f, strings + 0x27dc);
                }
                if (((GameSettings *)self->data)->serviceValue != 0) {
                    DrawText(self->text, 0x15e, 0xc0, 2, 1.0f, lbl_806D2DAC);
                } else {
                    DrawText(self->text, 0x15e, 0xc0, 4, 1.0f, lbl_806D2D94);
                }
            } else {
                if (((GameSettings *)self->data)->serviceValue != 0) {
                    DrawText(self->text, 0x2a, 0xc0, 3, 1.0f, strings + 0x27e8);
                } else {
                    DrawText(self->text, 0x2a, 0xc0, 3, 1.0f, strings + 0x2804);
                }
            }
            if (((GameSettings *)self->data)->mode == 0) {
                DrawText(self->text, 0x15e, 0xd8, 4, 1.0f, lbl_806D2D94);
            } else if (((GameSettings *)self->data)->mode == 1) {
                DrawText(self->text, 0x15e, 0xd8, 4, 1.0f, strings + 0x2708);
            } else {
                DrawText(self->text, 0x15e, 0xd8, 2, 1.0f, strings + 0x2714);
            }
            if (((GameSettings *)self->data)->vblank != 0) {
                DrawText(self->text, 0x15e, 0xf0, 2, 1.0f, lbl_806D2DAC);
            } else {
                DrawText(self->text, 0x15e, 0xf0, 4, 1.0f, lbl_806D2D94);
            }
            if (((GameSettings *)self->data)->option27 != 0) {
                DrawText(self->text, 0x15e, 0x108, 2, 1.0f, lbl_806D2E8C);
            } else {
                DrawText(self->text, 0x15e, 0x108, 4, 1.0f, lbl_806D2E94);
            }
            if (((GameSettings *)self->data)->cabinet == 1) {
                if (self->cursor != 5 || self->blink <= 0x1E) {
                    DrawText(self->text, 0x2a, 0x120, 7, 1.0f, strings + 0x2720);
                }
                if (((GameSettings *)self->data)->linkOption != 0) {
                    DrawText(self->text, 0x15e, 0x120, 4, 1.0f, lbl_806D2DAC);
                } else {
                    DrawText(self->text, 0x15e, 0x120, 2, 1.0f, lbl_806D2D94);
                }
            } else {
                if (((GameSettings *)self->data)->linkOption != 0) {
                    DrawText(self->text, 0x2a, 0x120, 3, 1.0f, strings + 0x272c);
                } else {
                    DrawText(self->text, 0x2a, 0x120, 3, 1.0f, strings + 0x2748);
                }
            }
            if (((GameSettings *)self->data)->flag44 != 0) {
                if (((GameSettings *)self->data)->flag45 != 0) {
                    DrawText(self->text, 0x15e, 0x138, 2, 1.0f, strings + 0x2764);
                } else {
                    DrawText(self->text, 0x15e, 0x138, 4, 1.0f, lbl_806D2E84);
                }
            } else {
                DrawText(self->text, 0x15e, 0x138, 4, 1.0f, lbl_806D2E50);
            }
        }
    }
    return 1;
}
#pragma use_lmw_stmw reset
#pragma exceptions reset
