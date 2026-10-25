extern void HSD_MObjSetTevStageCallback(int);

void KartItem_RenderCb_Mode7_Pre(void)
{
    HSD_MObjSetTevStageCallback(0);
}
