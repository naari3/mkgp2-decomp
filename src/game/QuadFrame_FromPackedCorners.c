extern void QuadFrame_FromCornerPtrs(float*,float*,float*,float*,float*,float*);
void QuadFrame_FromPackedCorners(float *corners,float *frame,float *height) { QuadFrame_FromCornerPtrs(corners,corners+3,corners+6,corners+9,frame,height); }
