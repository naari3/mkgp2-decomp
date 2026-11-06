# Map-effect parts anon_8016A2B8 (cxb_b2, 2026-11-04)

Source: Codex worker cxb_b2_mapfx16a_20261104 (gpt-6.1-sol/medium) + coordinator acceptance.

- Native exact: fn_8016A3D4 640B (Kiri16ACtor.cpp, real derived ctor + natural base cleanup, per-TU bridge), fn_8016A654 512B (Jungle16ADraw.cpp, HSD joint draw), fn_8016B32C 3060B (WeatherSystem_Update.c, weather/BGM tick).
- Kiri child/next getters must be null-first ternaries directly at the loop sites (helpers flip branch arms).
- Weather "playing" expression: cast the whole null-first int-return expression, `(unsigned char)(g_weatherSystem == 0 ? 0 : fn_80192010(id))`; otherwise the call branch is truncated and an extra cmpwi appears.
- Saturate_Double actually has float/float/float ABI (see Clamp.c). Literal 0/1 clamp limits give exact FP identities.
- Caution: tools/postprocess_sdata2.py renames by relocation offset without checking literal values; only trust its names once text offsets align (mismatching NM text can get wrong symbol names).
- Honest NonMatching: fn_8016A854 97.69% (GPR web identities + extra descriptor-pointer copy), fn_8016AB58 97.84% (real C++ new guards/base cleanup exact; pool materialization / GPR identities), fn_8016AF3C 93.31% (prologue pool/vtable register scheduling, next-DObj copy).

## c5_s18_fn801fbe14_20261105
Source: Codex worker c5_s18_fn801fbe14_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c5_s18: Jungle16AUpdate descriptor/index/hit declarations plus indexed descriptor access inside the loop removes the extra descriptor-copy instruction: direct objdiff 97.69481 -> 98.181816, text size 620 -> target 616, extab/extabindex both 100. Remaining differences are descriptor/stride r31/r30 swap and frame-increment FP identities. Naming frame/step/delay temps did not move FP allocation. Constructor declaration hoist and split descriptor cursor did not improve; fn_801FBE14 direct input load gets desired colors but adds mr, while inline getter/direct ternary retain swapped input/creditOnly registers. clModelM copy/helper/open-index probes did not improve. All remain honest NonMatching; final coordinator full build SHA-1 OK.

## c16_u128_20261106
Source: Codex worker c16_u128_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 1 fn / 916 B.

c16_u128: fn_801FBE14 (916B) input/creditOnly r30/r31 swap resolved by extracting the existing credit predicate into static inline unsigned char IsCreditOnly(), using early return 1 for play-state==3 and credit-count==0, else return 0. GetInput stays canonical. Whole update helper with input parameter was too large to inline and rejected. Final text/EH/index all100%, source-linked at801FBE14/916B, Matching promotion full DOL SHA1 exact. No new bridge or padding required.
