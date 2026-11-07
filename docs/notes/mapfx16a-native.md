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

## c17_u90_20261107
Source: Codex worker c17_u90_20261107 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c17_u90: Jungle16ACtor fresh direct objdiff 97.8421%. Keep indexed descriptor access ((const Desc16A*)((const char*)pool+0x488))[i] instead of advancing a reassigned descriptor cursor: loop becomes exact, function 99.789474% / 380 B, extab88/index12 exact. Remaining four register-field differences are only initial pool-base/vtable materialization (target lis r6, source r3). A real static shared pool of float weather curves, zone vertices, descriptor records and strings at 8036CA00..8036CF64 reproduces target prologue register setup and all 1380 B data, but source then advances descriptor r30 before motion-stride r29 at +11C/+124; target does the opposite. No filler used; final 4-byte alignment gap left outside pool. Named descriptor before allocations adds a copy; after allocations keeps the two-increment schedule. Explicit native weather-array base changes vector-copy scheduling. Pool experiment fully reverted; keep 99.789474% honest NM. Single function prevents mechanism B. Final full fallback DOL SHA1 exact.
