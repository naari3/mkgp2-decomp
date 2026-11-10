/* Figure flow round availability, 801C64DC. */
typedef struct {
    int v, cup; char pad08[0x1c-8]; void* message;
    char pad20[0xb8-0x20]; int unlocked;
    char padbc[8]; int rounds[4];
    char padd4[0x100-0xd4]; short *label, *value;
    char pad108[0x118-0x108]; unsigned char second;
} FigureUnlocks;
extern unsigned char g_playerData[];
extern short clFlowFigure_Unlocks_rodata_8039B218[];
extern void SetCourseParams(int,int,int,int);
extern unsigned char RoundIsUnlocked(void*,int);
/* Cup labels and their page/completion variants form blocks of eight IDs. */
typedef enum {
    FIGURE_LABEL_CUP_FIRST = 0x1EA2,
    FIGURE_LABEL_VARIANT_LAST = 0x1EB9
} FigureLabelId;
static inline FigureLabelId FigureLabel(FigureUnlocks* self) {
    int label = clFlowFigure_Unlocks_rodata_8039B218[self->cup];
    int page = self->second == 1 ? 8 : 0;
    return (FigureLabelId)(label + page);
}
#pragma exceptions on
void fn_801C64DC(FigureUnlocks* self) {
    unsigned char first;
    int i;
    int offset;
    if(self->cup == 0) SetCourseParams(7,0,0,0);
    if(self->cup == 1) SetCourseParams(1,0,0,0);
    if(self->cup == 2) SetCourseParams(8,0,0,0);
    if(self->cup == 3) SetCourseParams(2,0,0,0);
    if(self->cup == 4) SetCourseParams(3,0,0,0);
    if(self->cup == 5) SetCourseParams(4,0,0,0);
    if(self->cup == 6) SetCourseParams(5,0,0,0);
    if(self->cup == 7) SetCourseParams(6,0,0,0);
    self->unlocked=0;
    first=1;
    offset=self->second == 1 ? 4 : 0;
    for(i=0;i<4;i++) {
        if(RoundIsUnlocked(g_playerData,i+offset)) {
            self->rounds[i]=1; self->unlocked++;
        } else if(first) { self->rounds[i]=0; first=0; }
        else self->rounds[i]=-1;
    }
    if(self->message) {
        if(RoundIsUnlocked(g_playerData,self->second == 0 ? 3 : 7) == 1) {
            *self->label=0x175c;
            *self->value=FigureLabel(self)+8;
        } else {
            *self->label=0x175b;
            *self->value=clFlowFigure_Unlocks_rodata_8039B218[self->cup];
        }
    }
}
#pragma exceptions reset
