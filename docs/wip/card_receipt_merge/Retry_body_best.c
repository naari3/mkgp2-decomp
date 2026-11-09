int Sci2Card_BuildRetryReceiptLine(int line_p0)
{
char output_p0[0x1400];
char scratch_p0[0x200];
void *card_p0;
unsigned char update_p0;
unsigned char finish_p0;
const char *c_p0;
const char *b_p0;
const char *a_p0;
const char *d_p0;
finish_p0 = 0;
update_p0 = 0;
card_p0 = Sci2Card_Singleton_Get_p0();
if (line_p0 < 0) {
if (lbl_806D1225_p0 == 0) Sci2Card_SendCmdLedSet_p0(card_p0, 12, 1);
return line_p0 + 1;
}
memset_p0(output_p0, 0, 0x1400);
switch (line_p0) {
case 0:
memset_p0(scratch_p0, 0, 0x200) ;
sprintf_p0(output_p0, (((const RetryReceiptFormat_p0 *)lbl_80317DB0)[line_p0].format_p0) , (const char *)lbl_803180FC);
if (lbl_806D123C_p0 == line_p0) update_p0 = 1 ;
strcat_p0(output_p0, lbl_806D35BC_p0) ;
++line_p0;
break;
case 1: {
const char *text_p0;
memset_p0(scratch_p0, 0, 0x200) ;
if (isJapanese_p0() == 0) text_p0 = Sci2Card_GetReceiptStringEntry_p0(22);
else text_p0 = Sci2Card_GetReceiptStringEntry_p0(23);
sprintf_p0(scratch_p0, (((const RetryReceiptFormat_p0 *)lbl_80317DB0)[line_p0].format_p0) , text_p0, lbl_806D35C0_p0);
if (lbl_806D123C_p0 == line_p0) update_p0 = 1 ;
strcat_p0(output_p0, scratch_p0) ;
strcat_p0(output_p0, lbl_806D35C4_p0);
++line_p0;
break;
}
case 2:
memset_p0(scratch_p0, 0, 0x200) ;
if (lbl_806D123C_p0 == line_p0) update_p0 = 1 ;
sprintf_p0(scratch_p0, (((const RetryReceiptFormat_p0 *)lbl_80317DB0)[line_p0].format_p0) , lbl_806CF0F0_p0[isJapanese_p0()]);
strcat_p0(output_p0, scratch_p0) ;
strcat_p0(output_p0, lbl_806D35BC_p0) ;
++line_p0;
case 3:
memset_p0(scratch_p0, 0, 0x200) ;
if (lbl_806D123C_p0 == line_p0) update_p0 = 1 ;
sprintf_p0(scratch_p0, (((const RetryReceiptFormat_p0 *)lbl_80317DB0)[line_p0].format_p0) , 99999);
strcat_p0(output_p0, scratch_p0) ;
strcat_p0(output_p0, lbl_806D35BC_p0) ;
++line_p0;
case 4: {
const char *label_p0;
char *digits_p0;
const char *suffix_p0;
memset_p0(scratch_p0, 0, 0x200) ;
label_p0 = isJapanese_p0() == 0 ? (const char *)lbl_80318108 : lbl_806D35C8_p0;
digits_p0 = Retry_WinDigits_p0();
suffix_p0 = isJapanese_p0() == 0 ? lbl_806D35D8_p0 : lbl_806D35DC_p0;
sprintf_p0(scratch_p0, (((const RetryReceiptFormat_p0 *)lbl_80317DB0)[line_p0].format_p0) , label_p0, digits_p0, suffix_p0);
if (lbl_806D123C_p0 == line_p0) update_p0 = 1 ;
strcat_p0(output_p0, scratch_p0) ;
strcat_p0(output_p0, lbl_806D35BC_p0) ;
++line_p0;
break;
}
case 5:
memset_p0(scratch_p0, 0, 0x200) ;
if (lbl_806D123C_p0 == line_p0) update_p0 = 1 ;
sprintf_p0(scratch_p0, (((const RetryReceiptFormat_p0 *)lbl_80317DB0)[line_p0].format_p0) , (const unsigned char *)lbl_80318114);
strcat_p0(output_p0, scratch_p0) ;
strcat_p0(output_p0, lbl_806D35BC_p0) ;
++line_p0;
case 6:
memset_p0(scratch_p0, 0, 0x200) ;
if (lbl_806D123C_p0 == line_p0) update_p0 = 1 ;
sprintf_p0(scratch_p0, (((const RetryReceiptFormat_p0 *)lbl_80317DB0)[line_p0].format_p0) , (const unsigned char *)lbl_80318120);
strcat_p0(output_p0, scratch_p0) ;
strcat_p0(output_p0, lbl_806D35C4_p0);
++line_p0;
break;
case 7: {
memset_p0(scratch_p0, 0, 0x200) ;
a_p0 = Sci2Card_GetReceiptStringEntry_p0(6);
b_p0 = Sci2Card_GetReceiptStringEntry_p0(0);
c_p0 = Sci2Card_GetReceiptStringEntry_p0(7);
d_p0 = Sci2Card_GetReceiptStringEntry_p0(1);
sprintf_p0(scratch_p0, (((const RetryReceiptFormat_p0 *)lbl_80317DB0)[line_p0].format_p0) , Sci2Card_GetReceiptStringEntry_p0(18), a_p0, b_p0, c_p0, d_p0);
if (lbl_806D123C_p0 == line_p0) update_p0 = 1 ;
strcat_p0(output_p0, scratch_p0) ;
strcat_p0(output_p0, lbl_806D35BC_p0) ;
++line_p0;
break;
}
case 8: {
memset_p0(scratch_p0, 0, 0x200) ;
a_p0 = Sci2Card_GetReceiptStringEntry_p0(2);
b_p0 = Sci2Card_GetReceiptStringEntry_p0(3);
c_p0 = Sci2Card_GetReceiptStringEntry_p0(4);
d_p0 = Sci2Card_GetReceiptStringEntry_p0(5);
sprintf_p0(scratch_p0, (((const RetryReceiptFormat_p0 *)lbl_80317DB0)[line_p0].format_p0) , Sci2Card_GetReceiptStringEntry_p0(19), a_p0, b_p0, c_p0, d_p0);
if (lbl_806D123C_p0 == line_p0) update_p0 = 1 ;
strcat_p0(output_p0, scratch_p0) ;
strcat_p0(output_p0, lbl_806D35BC_p0) ;
++line_p0;
break;
}
case 9: {
finish_p0 = 1;
memset_p0(scratch_p0, 0, 0x200) ;
if (lbl_806D123C_p0 == line_p0) update_p0 = 1 ;
scratch_p0[0] = 'A';
scratch_p0[1] = 'A';
scratch_p0[2] = 'A';
scratch_p0[3] = 'A';
scratch_p0[4] = 'A';
scratch_p0[5] = 'A';
scratch_p0[6] = 'A';
scratch_p0[7] = 'A';
scratch_p0[8] = 'A';
scratch_p0[9] = 'A';
scratch_p0[10] = 'A';
scratch_p0[11] = 'A';
scratch_p0[12] = 'A';
scratch_p0[13] = 'A';
scratch_p0[14] = 'A';
scratch_p0[15] = 'A';
scratch_p0[16] = 'A';
scratch_p0[17] = 'A';
scratch_p0[18] = 'A';
scratch_p0[19] = 'A';
scratch_p0[20] = 'A';
scratch_p0[21] = 'A';
scratch_p0[22] = 'A';
scratch_p0[23] = 'A';
scratch_p0[24] = 'A';
scratch_p0[25] = 0;
strcat_p0(output_p0, scratch_p0) ;
++line_p0;
break;
}
default: return line_p0;
}
Sci2Card_SendCmdRegister_p0(card_p0, output_p0,
(unsigned char)(((const RetryReceiptFormat_p0 *)lbl_80317DB0)[line_p0 - 1].rows_p0 + 1),
finish_p0, update_p0);
return line_p0;
}
#pragma use_lmw_stmw reset
