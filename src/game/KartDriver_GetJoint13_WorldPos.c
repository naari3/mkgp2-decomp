/* World position of kart joint 13. */
extern void *KartDriver_GetJointByIdx(void *driver, int idx);
extern void Mtx44_GetTranslation_RowMajor(float *out, void *mtx);

void KartDriver_GetJoint13_WorldPos(float *out, void *driver)
{
    Mtx44_GetTranslation_RowMajor(out, KartDriver_GetJointByIdx(driver, 0xd));
}
