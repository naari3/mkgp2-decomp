# anon-801f8250-native-drafts

Source: Codex worker cxc_u10_f8250_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

801F8404 and 801F8728 naturally produce the exact primary DESTROYLOCAL EH action for a 32-byte float quad with inline empty destructor bridged to dtor_801F8214. Direct ctor drafts preserve exact target function sizes; FP allocation remains unmatched. 801F8A34 local is canonical ResCtrl, glyph walker is object-relative +0x24, and advances at +0x22C accumulate before each glyph including spaces/newlines. No source-closed claim; do not retry without a new structural hypothesis.

## c5_s17_fn801f8668_20261105
Source: Codex worker c5_s17_fn801f8668_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 1108 B.

fn_801F8668 matches with a const byte-pointer view of canonical DrawTables801F plus offsets A0/100/C0; this prevents redundant descriptor-address rematerialization. Same form does not solve fn_801F894C: offset zero generates an extra base copy and mr instead of target addi-zero. Typed inline helper also leaves original residual.

## c5_s16_anon8021f088_20261105
Source: Codex worker c5_s16_anon8021f088_20261105 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 2 fn / 392 B.

F8404: source-private DrawQuad8404 using named double fabs results before float narrowing restores initial product/fabs scheduling; ordering dx before sinPart improves text 97.05882 -> 98.59477. Remaining construction FP colors and first depth vertex y/z f1/f3 swap; exact size 612 and owned EH 100%, stays NonMatching.

## c14_u2_20261106
Source: Codex worker c14_u2_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u2: fn_801F8250 typed local pointer fmt = tables->mixedDepthFmt (or mixedFmt), then fmt += offset improves measured object 94.86239 to 96.33028 with owned EH 100%. Residual is only shift/base schedule in both branches: target slwi r0,r30,4 then addi r4,r31,field; source reverses those independent instructions. Byte-scaled offset declared before base and reversed pointer-add operands both emit identical code. Kept typed local form; no source-closed conclusion. Single-function TU cannot rescue an exact subset.

## c14_u7_20261106
Source: Codex worker c14_u7_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c14_u7: fn_801F8A34 improves 94.60199 -> 98.1592. Named local TextDraw801F* instead of parameter-cast macro plus counter initialization before sin/cos restores all target GPR homes. Block-local font width reused for normalAdvance and factor*width restores f1 load + fmr f28,f1 in both font branches. Remaining body glyph lhz is CSE-eliminated, compare and FP schedule differ; primary text800 vs804 B. Fully indexed glyph traversal regresses97.860695, reverted. Singleton remains NonMatching; full fallback-linked DOL SHA-1 OK. Three hypotheses exhausted; no source-closed claim.

## c16_u63_20261106
Source: Codex worker c16_u63_20261106 (gpt-6.1-sol/medium) + coordinator acceptance (independent main build, DOL SHA-1 OK, actual main.elf ranges). Native gain: 0 fn / 0 B.

c16_u63: fn_801F95A0 79.20588 -> 93.23529 under existing GC/2.6 flags. ID-taking inline ReleaseGlyph with table lookup inside helper gives target add r3/table/index then lwz +4 rather than folded addi+lwzx. Flatten outer loop helper; named TextDraw801F local from void* entry plus for-scoped counter restores early table lis r4 and counter r28. Remaining self/cursor r30/r29 versus target r29/r30 and prologue schedule. Owned 136B size/EH unchanged, extab/index 100%. Three structural hypotheses exhausted; no source-closed claim.
