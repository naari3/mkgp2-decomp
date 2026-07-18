typedef float Mtx[3][4];

extern void fn_8025D1B8(const Mtx src, Mtx dst);

void Mtx_Copy(Mtx dst, const Mtx src) {
    fn_8025D1B8(src, dst);
}
