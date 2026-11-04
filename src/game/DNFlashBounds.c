/* Reference-preserving extrema used by the flash trigger initializer. */
float fn_80228F80(const float *a, const float *b) { return *a > *b ? *a : *b; }
float fn_80228F98(const float *a, const float *b) { return *a < *b ? *a : *b; }
