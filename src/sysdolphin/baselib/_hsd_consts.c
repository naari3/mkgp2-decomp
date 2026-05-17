/* HSD shared sdata2 constants. mkgp2 binary keeps these as named globals
 * at 0x806DCC58 and 0x806DCC60, referenced by many HSD TUs via sda21 reloc.
 *
 * NOTE: file name is a placeholder. Real mkgp2 source likely emits these
 * literals from a yet-unidentified TU; sdata2 pool TU identification is
 * tracked separately. */

const float  lbl_806DCC58 = 0.0f;
const double lbl_806DCC60 = 4503601774854144.0;  /* 0x4330000080000000 */
