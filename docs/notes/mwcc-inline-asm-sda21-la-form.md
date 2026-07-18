# mwcc inline asm: sda21 address materialization with reloc

2026-07-19, batch_text_80039e10_volumecalibration (VolumeCalibration_DrawOverlay asm_fn).

mwcc 1.3.2 inline asm rejects `li rD, sym@sda21` and `addi rD, r2, sym`, but ACCEPTS:

```c
la r29, lbl_806D2480(r2)
```

which assembles to `addi r29, r2, sym` WITH the sda21 relocation (dtk displays `li r29, lbl_806D2480@sda21`). This gives objdiff 100% where the raw-offset spelling `addi r29, r2, -0x7DE0` is byte-identical in the final dol (SHA-1 OK) but shows <100% in objdiff/report because the target instruction carries a reloc.

`tools/extract_fn_asm.py` currently emits the raw-offset form for sda21 ADDRESS materialization (loads/stores already use the reloc-generating `sym(r2)` form). Candidate tool improvement: emit `la rD, sym(r2)` instead; would self-correct the <100% asm_fn TUs (e.g. FlowDispatcher_ScopedTimer 97.6%, auto_ONKARTHIT_block sites).
