typedef void (*DVDLoadCallback)(int result, void *user_data);

extern DVDLoadCallback lbl_806D1150;
extern void *lbl_806D1158;
extern int lbl_806D115C;

void DVDLoad_DrawDoneCallback(int result)
{
    lbl_806D115C = result;
    lbl_806D1150(result, lbl_806D1158);
}
