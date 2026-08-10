# HANDOFF unit_commbroadcast_core

The five functions in reversed-extab group `auto_03_800848C4_text` are kept together in one TU. They use exact `asm_fn` bodies; this group has no extab/extabindex entries, so no manual emit or rename map is required.

```json
{
  "batch_id": "unit_commbroadcast_core",
  "sub_summary": "CommBroadcast core 5-function bundle: exact asm_fn, SHA-1 OK",
  "results": [
    {
      "addr": "0x800848C4",
      "name": "CommBroadcast_GetKartLap",
      "status": "asm_fn",
      "src_path": "game/CommBroadcast.c",
      "objdiff_percent": 100.0,
      "notes": "Exact target body extracted from auto_03_800848C4_text; same-TU bundle preserved."
    },
    {
      "addr": "0x800848FC",
      "name": "CommBroadcast_SetKartLap",
      "status": "asm_fn",
      "src_path": "game/CommBroadcast.c",
      "objdiff_percent": 100.0,
      "notes": "Exact target body extracted from auto_03_800848C4_text; same-TU bundle preserved."
    },
    {
      "addr": "0x80084934",
      "name": "CommBroadcast_GetKartRankNibble",
      "status": "asm_fn",
      "src_path": "game/CommBroadcast.c",
      "objdiff_percent": 100.0,
      "notes": "Exact target body extracted from auto_03_800848C4_text; same-TU bundle preserved."
    },
    {
      "addr": "0x800849B8",
      "name": "CommBroadcast_SetKartRankNibble",
      "status": "asm_fn",
      "src_path": "game/CommBroadcast.c",
      "objdiff_percent": 100.0,
      "notes": "Exact target body extracted from auto_03_800848C4_text; same-TU bundle preserved."
    },
    {
      "addr": "0x80084A48",
      "name": "CommBroadcast_ScanForMySyncMatch",
      "status": "asm_fn",
      "src_path": "game/CommBroadcast.c",
      "objdiff_percent": 100.0,
      "notes": "Exact target body extracted from auto_03_800848C4_text; same-TU bundle preserved."
    }
  ],
  "configure_py": {
    "add_objects": [
      {
        "lib": "game",
        "object": "Object(Matching, \"game/CommBroadcast.c\")"
      }
    ]
  },
  "splits_txt": {
    "add_entries": [
      {
        "path": "game/CommBroadcast.c",
        "sections": [
          {
            "section": ".text",
            "start": "0x800848C4",
            "end": "0x80084A84"
          }
        ]
      }
    ]
  },
  "symbols_txt": {
    "set_scope": [],
    "set_attr": [],
    "rename": []
  },
  "docs_notes": [],
  "build_verified": {
    "command": "python configure.py && ninja build/GNLJ82/ok",
    "sha1_ok": true,
    "funcs_matched_delta": 5
  },
  "blocked_reason": null,
  "user_attention": null
}
```
