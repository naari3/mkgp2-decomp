extern void HSD_CObjEndCurrent(void *obj);

void CObj_GlobalProjPushFrame(void *obj)
{
    HSD_CObjEndCurrent(obj);
}
