/* Course select flow (0x801CE800..0x801D1800): one TU.
 * The TU owns .data 0x8049B1E0..0x8049B4A8 (row layouts, row animations,
 * cup map ids, then the compiler's RTTI/vtable and jump tables), .rodata
 * 0x8039B990..0x8039BF88 and the RTTI .sdata. clFlowCourse_Init addresses
 * the row table and the vtable off one pooled .data base.
 * Each former file keeps its own declarations in a namespace. */
#define CourseFlow clFlowCourse
#define CourseBase clFlowProcess
#define CLFLOWCOURSE_REAL_VTABLE
#include "game/clFlowCourse.h"
#include "game/singleton.h"
#include "game/CreditHud.h"

namespace course_rows {
#include "game/C8CourseRowsPrivate.h"
}

/* === .data 0x8049B1E0 === */
namespace course_data {
using course_rows::RowLayout;
using course_rows::RowAnimation;
extern "C" {
RowLayout clFlowCourse_data_8049B1E0[18] = {
    {0x19DC, 0x19E0, 0x19DE, 0, 92.0f, 260.0f, 245.0f},
    {0x19DD, 0x19E1, 0x19DF, 0, 158.0f, 168.0f, 188.0f},
    {0x19AC, 0x19B0, 0x19AF, 0, 214.0f, 260.0f, 245.0f},
    {0x19AD, 0x19B1, 0x19AE, 0, 282.0f, 168.0f, 188.0f},
    {0x19D1, 0x19D4, 0x19D2, 0, 336.0f, 260.0f, 245.0f},
    {0x19D0, 0x19D5, 0x19D3, 0, 404.0f, 168.0f, 188.0f},
    {0x1994, 0x1998, 0x1996, 0, 458.0f, 260.0f, 245.0f},
    {0x1995, 0x1999, 0x1997, 0, 526.0f, 168.0f, 188.0f},
    {0x1988, 0x198C, 0x198A, 0, 742.0f, 168.0f, 188.0f},
    {0x1989, 0x198D, 0x198B, 0, 818.0f, 260.0f, 245.0f},
    {0x19B8, 0x19BC, 0x19BA, 0, 874.0f, 168.0f, 188.0f},
    {0x19B9, 0x19BD, 0x19BB, 0, 932.0f, 260.0f, 245.0f},
    {0x19A0, 0x19A4, 0x19A2, 0, 986.0f, 168.0f, 188.0f},
    {0x19A1, 0x19A5, 0x19A3, 0, 1054.0f, 260.0f, 245.0f},
    {0x19C4, 0x19C8, 0x19C6, 0, 1108.0f, 168.0f, 188.0f},
    {0x19C5, 0x19C9, 0x19C7, 0, 1176.0f, 260.0f, 245.0f},
    {0, 0, 0, 0, 0.0f, 0.0f, 0.0f},
    {0, 0, 0, 0, 0.0f, 0.0f, 0.0f}
};
RowAnimation clFlowCourse_data_8049B348[8] = {
    {0, 1.0f}, {34, 1.0f}, {151, 1.0f}, {152, 1.0f},
    {150, 1.0f}, {364, 0.6f}, {440, 0.6f}, {113, 0.6f}
};
short clFlowCourse_data_8049B388[8][2] = {
    {0x1777, 0x1780}, {0x1778, 0x1781}, {0x1779, 0x1782}, {0x177A, 0x1783},
    {0x177B, 0x1784}, {0x177C, 0x1785}, {0x177D, 0x1786}, {0x177E, 0x1787}
};
}
}

