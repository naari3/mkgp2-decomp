extern void HSD_MObjSetTevStageCallback(int);

void KartItem_RenderCb_DefaultCycle_Pre(void)
{
    HSD_MObjSetTevStageCallback(0);
}
