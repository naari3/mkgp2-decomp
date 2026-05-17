extern void *lbl_806CED28[2];

void *SetActiveCamera(int idx, void *cam) {
    void *old = lbl_806CED28[idx];
    lbl_806CED28[idx] = cam;
    return old;
}
