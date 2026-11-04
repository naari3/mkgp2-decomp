# Map-effect parts anon_8016A2B8 (cxb_b2, 2026-11-04)

Source: Codex worker cxb_b2_mapfx16a_20261104 (gpt-6.1-sol/medium) + coordinator acceptance.

- Native exact: fn_8016A3D4 640B (Kiri16ACtor.cpp, real derived ctor + natural base cleanup, per-TU bridge), fn_8016A654 512B (Jungle16ADraw.cpp, HSD joint draw), fn_8016B32C 3060B (WeatherSystem_Update.c, weather/BGM tick).
- Kiri child/next getters must be null-first ternaries directly at the loop sites (helpers flip branch arms).
- Weather "playing" expression: cast the whole null-first int-return expression, `(unsigned char)(g_weatherSystem == 0 ? 0 : fn_80192010(id))`; otherwise the call branch is truncated and an extra cmpwi appears.
- Saturate_Double actually has float/float/float ABI (see Clamp.c). Literal 0/1 clamp limits give exact FP identities.
- Caution: tools/postprocess_sdata2.py renames by relocation offset without checking literal values; only trust its names once text offsets align (mismatching NM text can get wrong symbol names).
- Honest NonMatching: fn_8016A854 97.69% (GPR web identities + extra descriptor-pointer copy), fn_8016AB58 97.84% (real C++ new guards/base cleanup exact; pool materialization / GPR identities), fn_8016AF3C 93.31% (prologue pool/vtable register scheduling, next-DObj copy).
