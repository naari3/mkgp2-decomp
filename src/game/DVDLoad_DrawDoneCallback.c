typedef void (*DVDLoadCallback)(int result, void *user_data);

extern DVDLoadCallback DVDLoad_bss_806D1150;
extern void *DVDLoad_bss_806D1158;
extern int DVDLoad_bss_806D115C;

void DVDLoad_DrawDoneCallback(int result)
{
    DVDLoad_bss_806D115C = result;
    DVDLoad_bss_806D1150(result, DVDLoad_bss_806D1158);
}
