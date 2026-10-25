typedef float Mtx[3][4];

extern void PSMTXCopy(const Mtx src, Mtx dst);

void Mtx_Copy(Mtx dst, const Mtx src) {
    PSMTXCopy(src, dst);
}
