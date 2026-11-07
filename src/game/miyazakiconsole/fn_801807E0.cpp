#include "game/miyazakiconsole/miyazakiconsole.h"
#include "game/miyazakiconsole/console_draw_private.h"
extern "C" {
extern const TextBuffer lbl_80376E38;
extern int lbl_806D1664;
extern const char lbl_806D9248[4], lbl_806D924C[4], lbl_806D9250[4], lbl_806D9254[4], lbl_806D9258[4];
char *strncat(char *, const char *, unsigned long);
void fn_8017FF10(int, int, const char *, ...);
}
static inline void DrawBorderFrame(TextBuffer &buf, int x, int y, int lines) {
    int col;
    int row;
    for (row = 0; row < lines; row++) {
        buf.Clear();
        col = 0;
        do {
            if (row == 0 || row == lines - 1) {
                if (col == 0 || col == 34) strncat(buf.text, lbl_806D9248, 1);
                else strncat(buf.text, lbl_806D924C, 1);
            } else {
                if (col == 0 || col == 34) strncat(buf.text, lbl_806D9250, 1);
                else strncat(buf.text, lbl_806D9254, 1);
            }
        } while (++col < 35);
        fn_8017FF10(x, y + row, buf.text);
    }
}
extern "C" void fn_801807E0(Menu *m, int x, int y, unsigned char dim) {
    const char *strings = lbl_80376E38.text;
    if (m->count == 0) {
        TextBuffer buf = lbl_80376E38;
        DrawBorderFrame(buf, x, y, 4);
        fn_8017FF10(x+22, y, strings+0x100);
        fn_8017FF10(x+1, y+1, m->title);
        fn_8017FF10(x+2, y+2, strings+0x10c);
    } else {
        unsigned int start = 0;
        int lines;
        lines = (m->count < 9 ? m->count : 9) + 3;
        TextBuffer buf = *(const TextBuffer *)strings;
        DrawBorderFrame(buf, x, y, lines);
        fn_8017FF10(x+22, y, strings+0x11c, m->cursor+1, m->count);
        if (m->count > 9) {
            if (m->cursor < 4) start=0;
            else if (m->cursor+4 >= m->count) start=m->count-9;
            else start=m->cursor-4;
        }
        fn_8017FF10(x+1, y+1, m->title);
        int top;
        int i;
        MenuItem *item;
        item=m->head;
        top=y+2;
        for (i=0; i<m->count; i++) {
            if (item != 0) {
                if (i>=start && i<start+9) {
                    if (i==m->cursor) {
                        if (lbl_806D1664<=15 || !dim) fn_8017FF10(x+1, top+i-start, lbl_806D9258);
                    }
                    fn_8017FF10(x+2, top+i-start, item->name);
                }
                item=item->next;
            }
        }
    }
}
