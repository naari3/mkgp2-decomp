/* Dynamic initialization of the print message/configuration pointers.
 * The generated __sinit and .ctors entry match the original initializer.
 * Its symbol is local, as expected for compiler-generated initialization.
 * Configuration storage remains externally owned to avoid a reversed data
 * versus text link-order cycle with CardPrintFlowUpdate's switch table.
 */
extern "C" {
extern const char *const lbl_806DBF80, *const lbl_806DBF84;
extern const char *const lbl_806DBF88, *const lbl_806DBF8C;
extern const char *const lbl_806DBF90, *const lbl_806DBF94;
extern const char *const lbl_806DBF98, *const lbl_806DBF9C;
extern const int lbl_806DA848;
extern const char *CardPrintConfig_bss_806D1AA0, *CardPrintConfig_bss_806D1AA4;
extern const char *CardPrintConfig_bss_806D1AA8, *CardPrintConfig_bss_806D1AAC;
extern const char *CardPrintConfig_data_804EED20[12];
extern int lbl_806D1AB0;
}
struct CardPrintConfigInit {
    CardPrintConfigInit() {
        CardPrintConfig_bss_806D1AA0 = lbl_806DBF98;
        CardPrintConfig_bss_806D1AA4 = lbl_806DBF98;
        CardPrintConfig_bss_806D1AA8 = lbl_806DBF9C;
        CardPrintConfig_bss_806D1AAC = lbl_806DBF9C;
        CardPrintConfig_data_804EED20[0] = lbl_806DBF80;
        CardPrintConfig_data_804EED20[1] = lbl_806DBF84;
        CardPrintConfig_data_804EED20[2] = lbl_806DBF88;
        CardPrintConfig_data_804EED20[3] = lbl_806DBF8C;
        CardPrintConfig_data_804EED20[4] = lbl_806DBF90;
        CardPrintConfig_data_804EED20[5] = lbl_806DBF94;
        CardPrintConfig_data_804EED20[6] = lbl_806DBF98;
        CardPrintConfig_data_804EED20[7] = lbl_806DBF98;
        CardPrintConfig_data_804EED20[8] = lbl_806DBF98;
        CardPrintConfig_data_804EED20[9] = lbl_806DBF9C;
        CardPrintConfig_data_804EED20[10] = lbl_806DBF9C;
        CardPrintConfig_data_804EED20[11] = lbl_806DBF9C;
        lbl_806D1AB0 = lbl_806DA848;
    }
};
static CardPrintConfigInit printConfigInit;
/* MWCC emits __sinit after the source; retain its startup side effects. */
#pragma force_active on
