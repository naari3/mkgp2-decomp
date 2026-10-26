/* Dynamic initialization of the print message/configuration pointers.
 * The generated __sinit text and .ctors entry are exact, but this TU stays
 * NonMatching: the current build cannot retain/alias an EH-free local sinit.
 * Configuration storage remains externally owned to avoid a reversed data
 * versus text link-order cycle with CardPrintFlowUpdate's switch table.
 */
extern "C" {
extern const char *const lbl_806DBF80, *const lbl_806DBF84;
extern const char *const lbl_806DBF88, *const lbl_806DBF8C;
extern const char *const lbl_806DBF90, *const lbl_806DBF94;
extern const char *const lbl_806DBF98, *const lbl_806DBF9C;
extern const int lbl_806DA848;
extern const char *lbl_806D1AA0, *lbl_806D1AA4;
extern const char *lbl_806D1AA8, *lbl_806D1AAC;
extern const char *lbl_804EED20[12];
extern int lbl_806D1AB0;
}
struct CardPrintConfigInit {
    CardPrintConfigInit() {
        lbl_806D1AA0 = lbl_806DBF98;
        lbl_806D1AA4 = lbl_806DBF98;
        lbl_806D1AA8 = lbl_806DBF9C;
        lbl_806D1AAC = lbl_806DBF9C;
        lbl_804EED20[0] = lbl_806DBF80;
        lbl_804EED20[1] = lbl_806DBF84;
        lbl_804EED20[2] = lbl_806DBF88;
        lbl_804EED20[3] = lbl_806DBF8C;
        lbl_804EED20[4] = lbl_806DBF90;
        lbl_804EED20[5] = lbl_806DBF94;
        lbl_804EED20[6] = lbl_806DBF98;
        lbl_804EED20[7] = lbl_806DBF98;
        lbl_804EED20[8] = lbl_806DBF98;
        lbl_804EED20[9] = lbl_806DBF9C;
        lbl_804EED20[10] = lbl_806DBF9C;
        lbl_804EED20[11] = lbl_806DBF9C;
        lbl_806D1AB0 = lbl_806DA848;
    }
};
static CardPrintConfigInit printConfigInit;
