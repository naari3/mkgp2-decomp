#ifndef C8_COURSE_ROWS_PRIVATE_H
#define C8_COURSE_ROWS_PRIVATE_H
#include "game/CreditHud.h"
struct CourseRow { AnimSprite *sprite; int state; };
struct CourseRows { char pad0[0x14]; float x; char pad18[0xC]; CourseRow rows[1]; };
struct RowLayout { short a,b,c,pad; float x,y,alternateY; };
struct RowAnimation { int resource; float scale; };
struct RowSpriteView { int a,b,c; float x,y,scaleX,scaleY; };
extern "C" {
extern RowLayout clFlowCourse_data_8049B1E0[];
extern RowAnimation clFlowCourse_data_8049B348[];
extern const float lbl_806D9EF0;
unsigned char Sprite_AdvanceAnim(AnimSprite *, float);
void Sprite_SetupAnim(AnimSprite *, int, int, int);
void Sprite_SetAnimParam(AnimSprite *, short, short);
void fn_801A0550(AnimSprite *);
void fn_8019FF6C(AnimSprite *, int);
}
inline void SetRowScale(AnimSprite *p, float scale) {
    RowSpriteView *v = (RowSpriteView *)p;
    v->scaleX = scale; v->scaleY = scale;
}
#endif
