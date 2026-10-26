# HANDOFF throughput_roleb_20261026

All five native C++ functions matched, with original full-DOL SHA1. No helpers left running.

The first wiring attempt hit a cp932 Python read failure before metadata writes; retried with explicit UTF-8. Sjiswrap has no version switch; invocation with --version exited1 as it tried to open a program; SHA256 01D50FA1148CFC3C3B16658C6C9B1C0D9F5324CDE79ED6C09EF8353AF9D63ADF matches main supplied tool. Initial source object already had all text100. Final alias update did not trigger ninja dependency automatically, so an actual explanatory source comment was added and the source was recompiled. No timestamp manipulation. Target sessions39602 and73421 exited0; whole-DOL initial trial exited1 until aliases resolved, subsequent whole-DOL and final mandatory verification exited0.

Actual main.elf global symbols are at target addresses/sizes; symbol-table STT_FILE ordering is unsuitable for global symbol owner attribution, so proof uses exact source input in the main.elf link rule, fallback absence, object direct diff, and address-range payload equality. `build/roleb-diff.json` and `build/roleb-proof.json` retain detailed local evidence.

```json
{
  "batch_id": "throughput_roleb_20261026",
  "sub_summary": "Five genuine native C++ role variant B functions matched on first structural approach: 1204 bytes.",
  "results": [
    {
      "addr": "0x8024C564",
      "name": "fn_8024C564",
      "status": "matched",
      "src_path": "game/SceneRoleVariantB.cpp",
      "objdiff_percent": 100.0,
      "notes": "Genuine C++; automatic EH; first structural approach."
    },
    {
      "addr": "0x8024C6F0",
      "name": "fn_8024C6F0",
      "status": "matched",
      "src_path": "game/SceneRoleVariantB.cpp",
      "objdiff_percent": 100.0,
      "notes": "Genuine C++; automatic EH; first structural approach."
    },
    {
      "addr": "0x8024C818",
      "name": "fn_8024C818",
      "status": "matched",
      "src_path": "game/SceneRoleVariantB.cpp",
      "objdiff_percent": 100.0,
      "notes": "Genuine C++; automatic EH; first structural approach."
    },
    {
      "addr": "0x8024C944",
      "name": "fn_8024C944",
      "status": "matched",
      "src_path": "game/SceneRoleVariantB.cpp",
      "objdiff_percent": 100.0,
      "notes": "Genuine C++; automatic EH; first structural approach."
    },
    {
      "addr": "0x8024C9E0",
      "name": "fn_8024C9E0",
      "status": "matched",
      "src_path": "game/SceneRoleVariantB.cpp",
      "objdiff_percent": 100.0,
      "notes": "Genuine C++; automatic EH; first structural approach."
    }
  ],
  "configure_py": {
    "add_objects": [
      {
        "lib": "game",
        "object": "Object(Matching, \"game/SceneRoleVariantB.cpp\", extab_padding=b\"\", extra_cflags=[\"-Cpp_exceptions on\"])"
      }
    ]
  },
  "splits_txt": {
    "add_entries": [
      {
        "path": "game/SceneRoleVariantB.cpp",
        "sections": [
          {
            "section": ".text",
            "start": "0x8024C564",
            "end": "0x8024CA18"
          },
          {
            "section": "extab",
            "start": "0x8001E368",
            "end": "0x8001E444"
          },
          {
            "section": "extabindex",
            "start": "0x8002B598",
            "end": "0x8002B5D4"
          }
        ]
      }
    ]
  },
  "symbols_txt": {
    "set_scope": [],
    "rename": []
  },
  "extab_user_renames": {
    "src/game/SceneRoleVariantB.cpp": {
      "__nw__FUl": "Alloc",
      "__dl__FPv": "MemoryManager_TimedFree",
      "__vt__9RoleBRoot": "lbl_803FE0C8",
      "__vt__9RoleBBase": "lbl_804EEF58",
      "__vt__5RoleB": "lbl_804EEF04",
      "__dt__9RoleBRootFv": "dtor_8007D0D4",
      "__dt__9RoleBBaseFv": "dtor_8024CED0",
      "__dt__5RoleBFv": "fn_8024C6F0",
      "__dt__24VHolder<13FlowSceneList>Fv": "dtor_801F4B10",
      "__dt__20VHolder<10FlowFaderI>Fv": "dtor_801F2724",
      "__ct__16DoublyLinkedListFv": "DoublyLinkedList_Init",
      "__vt__13FlowSceneList": "lbl_804E533C",
      "__vt__13SceneListImpl": "lbl_804EC404",
      "__vt__9FlowFader": "lbl_80419DC8",
      "__vt__10FlowFaderI": "lbl_804E5284",
      "Set__10FlowFaderIFiis": "fn_8020A7CC",
      "__dt__21VHolder<10FlowFaderI>Fv": "dtor_801F2724",
      "__dt__10FlowFaderIFv": "fn_801F26C8",
      "@67": "@etb_8001E368",
      "@68": "@eti_8002B598",
      "@99": "@etb_8001E3E4",
      "@100": "@eti_8002B5A4",
      "@177": "@etb_8001E42C",
      "@178": "@eti_8002B5B0",
      "@190": "@etb_8001E434",
      "@191": "@eti_8002B5BC",
      "@200": "@etb_8001E43C",
      "@201": "@eti_8002B5C8"
    }
  },
  "docs_notes": [
    {
      "path": "docs/per_fn_matching_strategy.md",
      "content": "Role variant B 0x8024C564..8024CA18: genuine derived new factory, empty derived destructor with inline base destructor, and three route methods all match first structural approach (5 functions/1204B). Unique RoleBRoot/RoleBBase/RoleB model with canonical SceneListImpl, FlowFaderI and VHolder naturally emits factory DELETEPOINTER/DESTROYBASE/DESTROYMEMBER and two destructor SPECIFICATION islands. Explicit `(constant == flash->value) == 1` preserves fcmpu/mfcr/extrwi boolean sequence. Alias emitted weak FlowFaderI and VHolder destructors to existing definitions so their out-of-range copies are discarded; bridge automatic @67/@99/@177/@190/@200 EH names and paired index names. No manual EH or ASM. Text1204/EH220/index60 all100, linked native object, fullDOL SHA exact."
    }
  ],
  "build_verified": {
    "command": "python configure.py --compilers build/compilers --dtk build/tools/dtk.exe --objdiff build/tools/objdiff-cli.exe --sjiswrap build/tools/sjiswrap.exe; uv tool run --from ninja ninja -j4 all_source progress build/GNLJ82/report.json build/GNLJ82/ok",
    "sha1_ok": true,
    "funcs_matched_delta": 5,
    "native_bytes_delta": 1204,
    "actual_exit": 0,
    "full_dol_sha1": "ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65",
    "baseline": {
      "session": 39602,
      "exit": 0,
      "functions": 6370,
      "bytes": 1912700
    },
    "final": {
      "functions": 6375,
      "bytes": 1913904,
      "exit": 0
    },
    "direct_sections": {
      ".text": 100.0,
      "extab": 100.0,
      "extabindex": 100.0
    },
    "actual_main_elf": {
      "functions": [
        {
          "name": "fn_8024C564",
          "address": "0x8024c564",
          "size": 396,
          "binding": 1
        },
        {
          "name": "fn_8024C6F0",
          "address": "0x8024c6f0",
          "size": 296,
          "binding": 1
        },
        {
          "name": "fn_8024C818",
          "address": "0x8024c818",
          "size": 300,
          "binding": 1
        },
        {
          "name": "fn_8024C944",
          "address": "0x8024c944",
          "size": 156,
          "binding": 1
        },
        {
          "name": "fn_8024C9E0",
          "address": "0x8024c9e0",
          "size": 56,
          "binding": 1
        }
      ],
      "ranges": [
        {
          "start": "0x8024c564",
          "end": "0x8024ca18",
          "size": 1204,
          "main_elf_equals_original": true,
          "sha256": "05ca5dab4eb1170dff64afcb20c7a9a2963da1b476d50d1ae85e4baa6eaa8240"
        },
        {
          "start": "0x8001e368",
          "end": "0x8001e444",
          "size": 220,
          "main_elf_equals_original": true,
          "sha256": "df9bf3b3523064519ab45d7a143dec55d434d415e6deaf44483584e204fd66c5"
        },
        {
          "start": "0x8002b598",
          "end": "0x8002b5d4",
          "size": 60,
          "main_elf_equals_original": true,
          "sha256": "9f5e7d8a54dc43d1f6e8960af051020f9f58a0a23e050d8a29e53969c17c5a6e"
        }
      ],
      "linked_source": "build/GNLJ82/src/game/SceneRoleVariantB.o",
      "full_dol_sha1": "ea30f3b1cd90b133ce9affa3ffe3bb26408e7e65",
      "actual_main_elf_link_input_source": true,
      "actual_main_elf_link_input_fallback": false
    }
  },
  "timing": {
    "source_started_jst": "2026-10-26T10:33:51.9362332+09:00",
    "final_configure_started_jst": "2026-10-26T10:35:54.7366905+09:00",
    "setup_build_elapsed_seconds": null,
    "investigation_compile_elapsed_seconds_approx": 123,
    "approaches": 1,
    "baseline_session": 39602,
    "target_session": 73421,
    "sessions_terminal": true
  },
  "blocked_reason": null,
  "user_attention": null
}
```
