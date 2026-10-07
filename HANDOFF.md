# HANDOFF decompgabyou_dispatch_20261007

```json
{
  "batch_id": "decompgabyou_dispatch_20261007",
  "sub_summary": "GabyouItem_Dispatch_2Eto31: genuine complete plain C++ matched, 2388 text bytes plus native EH/index and native 40-byte switch table",
  "results": [
    {
      "addr": "0x800E7EC4",
      "name": "GabyouItem_Dispatch_2Eto31",
      "status": "matched",
      "src_path": "game/GabyouItemDispatch.cpp",
      "objdiff_percent": 100.0,
      "notes": "Full 0x954 body, no inline asm, manual EH, opwords, authored branch addresses, or neighboring functions. Native switch table is the sole owned .data range. Three material approaches A=98.56784%, B=99.61474%, C=100.0%."
    }
  ],
  "configure_py": {
    "add_objects": [
      {
        "lib": "game",
        "object": "Object(Matching, \"game/GabyouItemDispatch.cpp\", extra_cflags=[\"-Cpp_exceptions on\", \"-use_lmw_stmw on\"])"
      }
    ]
  },
  "splits_txt": {
    "add_entries": [
      {
        "path": "game/GabyouItemDispatch.cpp",
        "sections": [
          {"section": "extab", "start": "0x8000B59C", "end": "0x8000B5A4"},
          {"section": "extabindex", "start": "0x80023D80", "end": "0x80023D8C"},
          {"section": ".text", "start": "0x800E7EC4", "end": "0x800E8818"},
          {"section": ".data", "start": "0x80421188", "end": "0x804211B0"}
        ]
      }
    ]
  },
  "symbols_txt": {"set_scope": [], "set_attr": [], "rename": []},
  "metadata_changes": [],
  "provenance": {
    "baseline": "Fresh own worktree, original DOL copied by main. Foreground configure and ninja build/GNLJ82/ok finished exit 0 before source edits.",
    "target": "Read entire own build/GNLJ82/asm/auto_GabyouItem_Dispatch_text.s; confirmed sole .fn. Ghidra unavailable; ASM reconstruction only.",
    "abi": "Observed item+0xEC context, signed C8/C9/CB state fields, by-value Vec3 C++ call lowering, original pooled string base 8032EAB0. Read-only Tick/Fall source and Matrix4Multiply, Vec3, SoundMgr target ABI evidence.",
    "direct_comparison": "build/GNLJ82/gabyou_dispatch_C.json: target obj/game/GabyouItemDispatch.o vs real compiled src/game/GabyouItemDispatch.o. Text100%, extab100%, extabindex100%, .data100%; all instruction diff rows empty.",
    "compiler": "Production GC/1.3.2, C++ exceptions on, use_lmw_stmw on. Native compiler EH/table; no per-TU metadata renames needed.",
    "actual_link": "build.ninja main.elf link input at line13462 is build/GNLJ82/src/game/GabyouItemDispatch.o, not target obj fallback.",
    "report": "build/GNLJ82/report.json unit main/game/GabyouItemDispatch: complete=true, auto_generated=false, source_path=src/game/GabyouItemDispatch.cpp, matched_functions=1, complete_code=2388, all four sections100%."
  },
  "approach_ledger": [
    {"id": "A", "approach": "Complete typed plain C++ body with scoped loop/digit locals and expression-form camera normalization", "build_exit": 0, "text_percent": 98.56784, "text_size": 2380, "eh_percent": 100.0, "index_percent": 95.0, "data_percent": 100.0},
    {"id": "B", "approach": "Declare ones/tens/childIndex before context, modulo before quotient; matches callee-saved rank and duplicate division lowering", "build_exit": 0, "text_percent": 99.61474, "text_size": 2388, "eh_percent": 100.0, "index_percent": 100.0, "data_percent": 100.0},
    {"id": "C", "approach": "Camera magnitude reciprocal/product as named accumulator; literal zero tetherAngle removes alias-constrained load scheduling", "build_exit": 0, "text_percent": 100.0, "text_size": 2388, "eh_percent": 100.0, "index_percent": 100.0, "data_percent": 100.0}
  ],
  "docs_notes": [
    {
      "path": "docs/notes/gabyou-dispatch-native-match.md",
      "content": "GabyouItem_Dispatch_2Eto31 (800E7EC4, 0x954) matched in complete plain C++ with native 8B EH,12B index,40B ten-way switch table. Function-scope declaration order strings,ones,tens,childIndex,context produces r31 strings,r29 ones,r28 tens,r27 index,r26 context; implicit strength-reduced child walker uses r30. Compute ones=seconds%10 before tens=seconds/10 to reproduce two mulhwu instructions; quotient-first folds one division and shortens body8B. Camera normalization accumulator magnitude=1/magnitude; magnitude=distance*magnitude; magnitude=itemScale*magnitude coalesces into f1 and matches four FP rows. Literal0.0 tetherAngle assignment allows lfs-before-stb schedule that extern zero forbids. Existing pooled joint strings addressed from lbl_8032EAB0 with observed offsets; no string-pool ownership absorbed. All four sections direct100 and actual source-linked original SHA verified."
    }
  ],
  "build_verified": {
    "command": "C:/Users/optim/AppData/Roaming/uv/python/cpython-3.11-windows-x86_64-none/python.exe configure.py; ninja build/GNLJ82/ok; ninja progress",
    "configure_exit": 0,
    "ninja_exit": 0,
    "progress_exit": 0,
    "sha1_ok": true,
    "sha1": "ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65",
    "funcs_matched_delta": 1,
    "target_matched_functions": 1,
    "final_progress_functions": 1044,
    "final_progress_total_functions": 7614,
    "gain_bytes": 2388,
    "running_builds": false
  },
  "blocked_reason": null,
  "user_attention": null
}
```

Only source, configure object, and four exact split ranges change. Symbols and metadata remain unchanged. Source covers all initialization, signed state/kind dispatch, child cleanup, common transform, digit joint matrices and positional sound, auxiliary effects, camera-normalized offset, and four timers. Existing local semantic views are TU-private and include only observed fields.
