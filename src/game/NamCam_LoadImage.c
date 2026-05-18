/*
 * NamCam_LoadImage @ 0x80048BEC (size 0x48).
 *
 * Thin wrapper for Asset_LoadAndDecompressByType (Asset_LoadAndDecompressByType) that loads a
 * NamCam image. Three caller-visible args (imageData, imageId, pParams) are
 * forwarded as the wider callee signature with the decoder type set to 3
 * (-> fn_8029BCF0 dispatch path) and a stack byte argument of 0xFF.
 *
 * The Ghidra decompile shows only 4 args, but the real callee consumes
 * r3-r10 plus a stack byte at 0xB(r1). Writing the wrapper with the wider
 * prototype is required to make CW issue `mr r5, r6` register shuffling
 * (per docs/per_fn_matching_strategy.md §18 -- 3-arg pass-through forwarding).
 *
 * extab/extabindex entries are auto-emitted by CW under #pragma exceptions on
 * (same approach as ItemDisplay_Destroy).
 */

extern int Asset_LoadAndDecompressByType(
    void *path, void *decoderType, void *outBuf, int outSize,
    int alt7, int type, int alt9, int alt10, int stack_arg);

#pragma exceptions on
void NamCam_LoadImage(void *imageData, int imageId, void *pParams) {
    Asset_LoadAndDecompressByType(imageData, pParams, (void *)imageId, 0, 0, 3, 0, 0, 0xFF);
}
#pragma exceptions reset
