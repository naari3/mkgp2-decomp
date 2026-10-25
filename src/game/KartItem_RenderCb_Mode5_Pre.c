extern void HSD_MObjSetTevStageCallback(int);

void KartItem_RenderCb_Mode5_Pre(void)
{
    HSD_MObjSetTevStageCallback(0);
}
